#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "btree.h"

#define MAX_COLUMNS 10
#define MAX_ROWS 100

Table myclient;

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void display_table(Table* table) {
    if (table->column_count == 0) {
        printf("No table created.\n");
        return;
    }

    // Display column headers
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

    // Display table data
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

void insert_row(Table* table, char values[MAX_COLUMNS][50]) {
    if (table->row_count >= MAX_ROWS) {
        printf("Error: maximum number of rows reached.\n");
        return;
    }
    // Copy values into the new row
    for (int i = 0; i < table->column_count; i++) {
        strncpy(table->rows[table->row_count].data[i], values[i], 50);
    }

    // Use the first column as the key for the tree (e.g., id)
    int key = atoi(values[0]);
    table->index = insert_node(table->index, key, table->row_count);

    table->row_count++;
    printf("Row inserted successfully!\n");
}

void start_repl() {
    char command[256];  // Buffer to read commands

    printf("Welcome to myclient!\n");
    printf("Available commands:\n");
    printf("  - CREATE TABLE\n");
    printf("  - INSERT\n");
    printf("  - SELECT\n");
    printf("  - SHOW TREE\n");
    printf("  - EXIT\n\n");

    while (1) {
        printf("myclient > ");  // Display the prompt
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;  // Exit if EOF is reached
        }

        // Remove the newline at the end
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "EXIT") == 0) {
            printf("Goodbye!\n");
            break;
        } else if (strcmp(command, "INSERT") == 0) {
            if (myclient.column_count == 0) {
                printf("Error: no table created. Please use CREATE TABLE first.\n");
                continue;
            }

            char values[MAX_COLUMNS][50];
            printf("Enter values for the %d columns: \n", myclient.column_count);
            for (int i = 0; i < myclient.column_count; i++) {
                printf("%s: ", myclient.column_names[i]);
                if (fgets(values[i], sizeof(values[i]), stdin) == NULL) {
                    printf("Error reading value.\n");
                    continue;
                }
                values[i][strcspn(values[i], "\n")] = '\0'; // Remove newline character
            }

            insert_row(&myclient, values);
        } else if (strcmp(command, "SELECT") == 0) {
            if (myclient.column_count == 0) {
                printf("Error: no table created. Please use CREATE TABLE first.\n");
                continue;
            }

            printf("Table content:\n");
            display_table(&myclient);

        } else if (strcmp(command, "CREATE TABLE") == 0) {
            if (myclient.column_count > 0) {
                printf("Error: a table has already been created. Use SELECT to display the table.\n");
                continue;
            }

            printf("How many columns would you like? (max %d): ", MAX_COLUMNS);
            char input[10];
            int col_count;

            // Read the number of columns with fgets and convert it to an integer
            if (fgets(input, sizeof(input), stdin) == NULL || (col_count = atoi(input)) <= 0 || col_count > MAX_COLUMNS) {
                printf("Invalid number of columns. Please try again.\n");
                continue;
            }

            // Initialize the table
            myclient.row_count = 0;
            myclient.index = NULL;
            myclient.column_count = col_count;

            // Read the column names
            printf("Enter the names of the columns (one at a time):\n");
            for (int i = 0; i < col_count; i++) {
                printf("Column name %d: ", i + 1);
                if (fgets(myclient.column_names[i], sizeof(myclient.column_names[i]), stdin) == NULL) {
                    printf("Error reading column name.\n");
                    continue;
                }
                // Remove newline character left by fgets
                myclient.column_names[i][strcspn(myclient.column_names[i], "\n")] = '\0';
            }

            printf("Table created successfully!\n");
            display_table(&myclient);

        } else if (strcmp(command, "SHOW TREE") == 0) {
            if (myclient.index == NULL) {
                printf("The tree is empty.\n");
            } else {
                printf("Binary tree content:\n");
                print_tree(myclient.index);
            }

        } else {
            printf("Unknown command. Try CREATE TABLE, EXIT, INSERT, or SELECT.\n");
        }
    }
}
