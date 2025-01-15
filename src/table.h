// table.h
#ifndef TABLE_H
#define TABLE_H


#include <stddef.h> 
#include "row.h"

#define TABLE_NAME_SIZE 64

typedef struct {
    char name[TABLE_NAME_SIZE];
    Row *rows;
    size_t row_count;
} Table;

Table *create_table(const char *name);
void insert_row(Table *table, Row *row);
void select_rows(Table *table);
void free_table(Table *table);

#endif // TABLE_H