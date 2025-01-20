#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

// Créer un nouveau nœud
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

// Supprimer un nœud de l'arbre
Node* delete_node(Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = delete_node(root->left, key);
    } else if (key > root->key) {
        root->right = delete_node(root->right, key);
    } else {
        // Nœud à supprimer trouvé

        // Cas 1 : Nœud avec un seul enfant ou aucun enfant
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Cas 2 : Nœud avec deux enfants, obtenir le successeur en ordre
        Node* temp = find_min(root->right);  // Trouver le nœud avec la plus petite clé à droite
        root->key = temp->key;
        root->row_index = temp->row_index;
        root->right = delete_node(root->right, temp->key);  // Supprimer le successeur
    }
    return root;
}

// Trouver le nœud avec la clé minimale (successeur en ordre)
Node* find_min(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}
