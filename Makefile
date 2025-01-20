# Variables
CC = gcc
CFLAGS = -Wall -Werror -std=c99
TARGET = bin/myclient

# Fichiers sources et objets
SRCS = src/main.c src/btree.c src/repl.c
OBJS = bin/main.o bin/btree.o bin/repl.o

# Règle principale
all: $(TARGET)

# Lien final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compilation des fichiers objets
bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f bin/*.o $(TARGET)
