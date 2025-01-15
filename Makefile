# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -std=c11
LDFLAGS =
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIBS = -lmysqlclient  # Lien vers la bibliothèque MySQL

TARGET = $(BIN_DIR)/mycli

# Liste des fichiers sources
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Génération des fichiers objets correspondants
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Règle principale
all: $(TARGET)

# Règle pour construire l'exécutable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Règle pour compiler les fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

# Exécution du programme
run: all
	@./$(TARGET)

# Règle pour tester
test: all
	@echo "Tests à implémenter"

# Phony targets
.PHONY: all clean run test
