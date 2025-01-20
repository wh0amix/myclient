#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

//  Créer un nouveau nœud
Node* create_node(int key, int row_index) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (!new_node) {
		fprintf(stderr, "Erreur : allocation de mémoire échouée.\n");
		exit(EXIT_FAILURE);
	}
	new_node->key = key;
	new_node->row_index = row_index;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

// Insérer un nœud dans l'arbre
Node* insert_node(Node* root, int key, int row_index) {
	if (root == NULL) {
		return create_node(key, row_index);
	}
	if (key < root->key) {
		root->left = insert_node(root->left, key, row_index);
	} else if (key > root->key) {
		root->right = insert_node(root->right, key, row_index);
	} 
	return root;

}


// Rechercher un nœud par clé
Node* search_node(Node* root, int key) {
	if (root == NULL || root->key == key) {
		return root;
	}
	if (key < root->key) {
		return search_node(root->left, key);
	}
	return search_node(root->right, key);
}

// Fonction pour afficher l'arbre en ordre croissant
void print_tree(Node* root) {
	if (root != NULL) {
		print_tree(root->left);
		printf("Clé : %d, Ligne : %d\n", root->key, root->row_index);
		print_tree(root->right);
	}
}

