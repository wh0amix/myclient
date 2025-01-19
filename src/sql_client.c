// sql_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "sql_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "sql_client.h"

// Fonction pour initialiser la connexion MySQL
void init_connection(MYSQL **conn) {
    *conn = mysql_init(NULL);
    if (*conn == NULL) {
        fprintf(stderr, "Erreur d'initialisation: %s\n", mysql_error(*conn));
        exit(1);
    }
    if (mysql_real_connect(*conn, "localhost", "root", "password", NULL, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Erreur de connexion: %s\n", mysql_error(*conn));
        mysql_close(*conn);
        exit(1);
    }
}

// Fonction pour créer une base de données
void create_database(MYSQL *conn) {
    const char *query = "CREATE DATABASE IF NOT EXISTS mydb";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erreur de création de la base de données: %s\n", mysql_error(conn));
    } else {
        printf("Base de données créée avec succès.\n");
    }
}

void insert_record(MYSQL *conn) {
    const char *query = "INSERT INTO my_table (id, data) VALUES (1, 'Data1')";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erreur d'insertion: %s\n", mysql_error(conn));
    } else {
        printf("Enregistrement inséré avec succès.\n");
    }
}


void close_connection(MYSQL *conn) {
    mysql_close(conn);
}


// Fonction pour exécuter une requête SQL
void execute_query(MYSQL *conn, const char *query) {
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erreur dans la requête: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL) {
        if (mysql_field_count(conn) == 0) {
            printf("Requête exécutée avec succès.\n");
        } else {
            fprintf(stderr, "Erreur lors de la récupération des résultats: %s\n", mysql_error(conn));
        }
        return;
    }

    // Affichage des résultats pour une requête SELECT
    MYSQL_ROW row;
    unsigned int num_fields = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res))) {
        for (unsigned int i = 0; i < num_fields; i++) {
            printf("%s\t", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    mysql_free_result(res);
}

