#include <stdio.h>
#include <string.h>  // Ajoutez l'inclusion de string.h pour strcspn et strcmp
#include "table.h"
#include "row.h"
#include "utils.h"
#include "sql_client.h"  // Assurez-vous que sql_client.h est bien inclus

int main() {
    MYSQL *conn;
    char query[1024];

    // Initialisation de la connexion MySQL
    init_connection(&conn);

    printf("Welcome to MyCLI!\n");

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
