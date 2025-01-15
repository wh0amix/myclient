// row.h
#ifndef ROW_H
#define ROW_H

#define ROW_DATA_SIZE 128

typedef struct {
    int id;
    char data[ROW_DATA_SIZE];
} Row;

void init_row(Row *row, int id, const char *data);

#endif // ROW_H