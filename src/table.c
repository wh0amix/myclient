// table.c
#include "table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Table *create_table(const char *name) {
    Table *table = (Table *)malloc(sizeof(Table));
    if (table) {
        strncpy(table->name, name, TABLE_NAME_SIZE);
        table->name[TABLE_NAME_SIZE - 1] = '\0';
        table->rows = NULL;
        table->row_count = 0;
    }
    return table;
}

void insert_row(Table *table, Row *row) {
    if (!table || !row) return;
    table->rows = (Row *)realloc(table->rows, (table->row_count + 1) * sizeof(Row));
    if (table->rows) {
        table->rows[table->row_count] = *row;
        table->row_count++;
    }
}

void select_rows(Table *table) {
    if (!table) return;
    for (size_t i = 0; i < table->row_count; i++) {
        printf("ID: %d, Data: %s\n", table->rows[i].id, table->rows[i].data);
    }
}

void free_table(Table *table) {
    if (table) {
        free(table->rows);
        free(table);
    }
}