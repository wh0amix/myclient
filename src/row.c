// row.c
#include "row.h"
#include <string.h>

void init_row(Row *row, int id, const char *data) {
    if (row) {
        row->id = id;
        strncpy(row->data, data, ROW_DATA_SIZE);
        row->data[ROW_DATA_SIZE - 1] = '\0';
    }
}
