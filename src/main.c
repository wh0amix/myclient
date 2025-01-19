//main.c

#include <stdio.h>
#include <string.h>  
#include "table.h"
#include "row.h"
#include "utils.h"
#include "sql_client.h" 

#include <stdio.h>
#include <string.h>
#include "table.h"
#include "row.h"
#include "utils.h"
#include "sql_client.h"

int main() {
    MYSQL *conn;
    char query[1024];

    // Initialisation de la connexion MySQL
    init_connection(&conn);

    printf("Welcome to MyCLI!\n");

    // Créer la base de données
    create_database(conn);

    // Créer une table
    create_table("my_table");

    // Insérer un enregistrement dans la table
    insert_record(conn);

    // Boucle principale pour accepter les requêtes utilisateur
    while (1) {
        printf("mycli> ");
        
        // Lire la commande de l'utilisateur
        if (fgets(query, sizeof(query), stdin) == NULL) {
            break;  // Quitter en cas d'erreur de lecture
        }

        // Enlever le saut de ligne à la fin de la commande
        query[strcspn(query, "\n")] = 0;

        // Commande pour quitter le programme
        if (strcmp(query, "exit") == 0) {
            break;
        }

        // Exécution de la requête SQL sur MySQL
        execute_query(conn, query);
    }

    // Fermeture de la connexion MySQL
    close_connection(conn);
    printf("Merci d'avoir utilisé MyCLI. À bientôt!\n");

    return 0;
}


