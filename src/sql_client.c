// sql_client.c
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
    if (mysql_real_connect(*conn, "localhost", "root", "password", "mydb", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Erreur de connexion: %s\n", mysql_error(*conn));
        mysql_close(*conn);
        exit(1);
    }
}

// Fonction pour fermer la connexion MySQL
void close_connection(MYSQL *conn) {
    mysql_close(conn);
}

// Fonction pour exécuter la requête SQL
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
