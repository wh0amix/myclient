# Projet myclient

Ce projet implémente un gestionnaire de données en ligne de commande, développé en **C**, permettant l'exécution de commandes similaires à SQL.

## Fonctionnalités :
- **NOUVELLE TABLE** : Crée une nouvelle table avec un nombre défini de colonnes et leurs noms.
- **AJOUTER** : Insère des données dans la table, ligne par ligne, cellule par cellule.
- **EXTRAIRE** : Affiche l'intégralité du contenu de la table.
- **AFFICHAGE ARBORESCENT** : Organise et affiche les données dans une structure arborescente en utilisant une clé primaire.
- **FERMER** : Quitte le programme.

Ce projet a pour objectif d'appliquer et de maîtriser les concepts suivants :
1. La gestion des structures de données en **C** (tableaux, arbres binaires).
2. La création d'une interface ligne de commande interactive (REPL).
3. L'architecture modulaire d'un projet.

---

## **Caractéristiques principales**
1. **Création dynamique des tables :**
   - L'utilisateur choisit le nombre de colonnes (maximum 5) et leur nom.
   - Les tables peuvent contenir jusqu'à 100 lignes.

2. **Gestion des données avec un arbre binaire :** (fonctionnalité en développement)
   - Les données sont indexées dans un arbre binaire en utilisant la première colonne comme clé.
   - L'arbre facilite la recherche et l'affichage trié des données.

3. **Interface interactive :**
   - Les commandes sont directement saisies dans le terminal.
   - Des messages explicites guident l'utilisateur tout au long du processus.

---

## **Prérequis**
- Un compilateur (par exemple, GCC).
- Une distribution Linux (testée sous Debian).
- **Make** installé pour automatiser la compilation.

---

## **Structure du projet**
- `src/` : Contient les fichiers source du projet.
  - `main.c` : Point d'entrée principal.
  - `btree.c` et `btree.h` : Gestion des structures d'arbre binaire.
  - `repl.c` et `repl.h` : Interface REPL et logique des commandes SQL.
- `src/` : Contient les fichiers binaires du projet
- `Makefile` : Automatisation de la compilation.
- `README.md` : Documentation du projet.

---

## **Compilation et exécution**
1. Clonez ou téléchargez le projet.
2. Assurez-vous d'avoir un compilateur compatible C99.
3. Compilez le projet avec `make`.
4. Exécutez le programme avec `./bin/myclient`.

---

## **Commandes de base**
- **CREATE TABLE** : Créez une table.
- **SELECT** : Affichez la table.
- **INSERT** : Insérez des éléments dans la table.
- **SHOW TREE** : Affichez l'arbre binaire
- **EXIT** : Quittez.

   
