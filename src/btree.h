#ifndef BTREE_H
#define BTREE_H

// Définition de la structure Node
typedef struct Node {
	int key;
	int row_index;
	struct Node* left;
	struct Node* right;
} Node;



#define MAX_COLUMNS 10 // Nombre maximal de colonnes
#define MAX_ROWS 100  // Limite arbitraire de lignes pour simplifier

typedef struct Row {
	char data[MAX_COLUMNS][50];  // Données pour chaque colonne
} Row;

typedef struct Table {
	int column_count;         // Nombre de colonnes
	char column_names[MAX_COLUMNS][50]; // Noms des colonnes
	Row rows[MAX_ROWS];       // Stockage des lignes
	int row_count;            // Nombre actuel de lignes
	Node * index;		// Arbre binaire pour indexer les lignes
} Table;



// Déclaration des fonctions pour gérer l'arbre binaire et insérer une ligne
void print_tree(Node* root);
void insert_row(Table* table, char values[MAX_COLUMNS][50]);
Node* create_node(int key, int row_index);
Node* insert_node(Node* root, int key, int row_index);
Node* search_node(Node* root, int key);
Node* delete_node(Node* root, int key);
Node* find_min(Node* root);
void print_in_order(Node* root);

#endif
