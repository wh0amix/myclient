#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "btree.h"

#define MAX_COLUMNS 10
#define MAX_ROWS 100

Table myclient;
// Fonction pour effacer le buffer d'entrée
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Fonction pour afficher la table
void display_table(Table* table) {
    if (table->column_count == 0) {
        printf("Aucune table créée.\n");
        return;
    }

    printf("+");
    for (int i = 0; i < table->column_count; i++) {
        printf("---------------+");
    }
    printf("\n|");
    for (int i = 0; i < table->column_count; i++) {
        printf(" %-13s |", table->column_names[i]);
    }
    printf("\n+");
    for (int i = 0; i < table->column_count; i++) {
        printf("---------------+");
    }
    printf("\n");

    for (int r = 0; r < table->row_count; r++) {
        printf("|");
        for (int c = 0; c < table->column_count; c++) {
            printf(" %-13s |", table->rows[r].data[c]);
        }
        printf("\n");
    }
    printf("+");
    for (int i = 0; i < table->column_count; i++) {
        printf("---------------+");
    }
    printf("\n");
}

// Fonction pour insérer une ligne dans la table
void insert_row(Table* table, char values[MAX_COLUMNS][50]) {
    if (table->row_count >= MAX_ROWS) {
        printf("Erreur : nombre maximum de lignes atteint.\n");
        return;
    }
    for (int i = 0; i < table->column_count; i++) {
        strncpy(table->rows[table->row_count].data[i], values[i], 50);
    }

    int key = atoi(values[0]);  // Utilise la première colonne comme clé
    table->index = insert_node(table->index, key, table->row_count);  // Insertion dans l'arbre

    table->row_count++;
    printf("Ligne insérée avec succès !\n");
}

// Fonction pour supprimer une ligne par ID
void delete_row(Table* table, int id) {
    Node* found_node = search_node(table->index, id);  // Recherche dans l'arbre

    if (found_node == NULL) {
        printf("Erreur : ligne avec l'ID %d non trouvée.\n", id);
        return;
    }

    int row_index = found_node->row_index;  // Récupère l'index de la ligne à partir du nœud

    // Déplace les lignes pour supprimer celle correspondant à l'index trouvé
    for (int i = row_index; i < table->row_count - 1; i++) {
        table->rows[i] = table->rows[i + 1];  // Décale les lignes
    }
    table->row_count--;  // Réduit le nombre de lignes

    table->index = delete_node(table->index, id);  // Supprime de l'arbre
    printf("Ligne avec l'ID %d supprimée avec succès.\n", id);
}

// Fonction pour démarrer la REPL (interface en ligne de commande)
void start_repl() {
    char command[256];

    printf("Bienvenue dans Myclient !\n");
    printf("Commandes disponibles :\n");
    printf("  - CREATE TABLE\n");
    printf("  - INSERT\n");
    printf("  - SELECT\n");
    printf("  - DELETE\n");
    printf("  - SHOW TREE\n");
    printf("  - EXIT\n\n");

    while (1) {
        printf("Myclient > ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }
        command[strcspn(command, "\n")] = '\0';  // Supprime le saut de ligne

        if (strcmp(command, "EXIT") == 0) {
            printf("Au revoir !\n");
            break;
        } else if (strcmp(command, "INSERT") == 0) {
            if (myclient.column_count == 0) {
                printf("Erreur : aucune table n'a été créée. Utilisez CREATE TABLE d'abord.\n");
                continue;
            }

            char values[MAX_COLUMNS][50];
            printf("Entrez les valeurs pour les %d colonnes : \n", myclient.column_count);
            for (int i = 0; i < myclient.column_count; i++) {
                printf("%s : ", myclient.column_names[i]);
                if (fgets(values[i], sizeof(values[i]), stdin) == NULL) {
                    printf("Erreur lors de la lecture de la valeur.\n");
                    continue;
                }
                values[i][strcspn(values[i], "\n")] = '\0';
            }

            insert_row(&myclient, values);
        } else if (strcmp(command, "SELECT") == 0) {
            if (myclient.column_count == 0) {
                printf("Erreur : aucune table n'a été créée. Utilisez CREATE TABLE d'abord.\n");
                continue;
            }

            printf("Contenu de la table :\n");
            display_table(&myclient);
        } else if (strcmp(command, "CREATE TABLE") == 0) {
            if (myclient.column_count > 0) {
                printf("Erreur : une table a déjà été créée. Utilisez SELECT pour afficher la table.\n");
                continue;
            }

            printf("Combien de colonnes voulez-vous ? (max %d) : ", MAX_COLUMNS);
            char input[10];
            int col_count;

            if (fgets(input, sizeof(input), stdin) == NULL || (col_count = atoi(input)) <= 0 || col_count > MAX_COLUMNS) {
                printf("Nombre de colonnes invalide. Réessayez.\n");
                continue;
            }

            myclient.row_count = 0;
            myclient.index = NULL;
            myclient.column_count = col_count;

            printf("Entrez les noms des colonnes (un par un) :\n");
            for (int i = 0; i < col_count; i++) {
                printf("Nom de la colonne %d : ", i + 1);
                if (fgets(myclient.column_names[i], sizeof(myclient.column_names[i]), stdin) == NULL) {
                    printf("Erreur lors de la lecture du nom de la colonne.\n");
                    continue;
                }
                myclient.column_names[i][strcspn(myclient.column_names[i], "\n")] = '\0';
            }

            printf("Table créée avec succès !\n");
            display_table(&myclient);
        } else if (strncmp(command, "DELETE", 6) == 0) {
            int id = atoi(command + 7);  // Extraire l'ID après "DELETE "
            if (id == 0) {
                printf("Erreur : ID invalide.\n");
                continue;
            }
            delete_row(&myclient, id);
        } else if (strcmp(command, "SHOW TREE") == 0) {
            if (myclient.index == NULL) {
                printf("L'arbre est vide.\n");
            } else {
                printf("Contenu de l'arbre binaire :\n");
                print_tree(myclient.index);
            }
        } else {
            printf("Commande inconnue. Essayez CREATE TABLE, EXIT, INSERT, SELECT, DELETE ou SHOW TREE.\n");
        }
    }
}

