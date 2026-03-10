#ifndef lab2_h
#define lab2_h

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int number;
    char *string;
    char *value;
} TableData;

bool read_table(TableData table[], int table_limit, char *filepath, int *lines);
bool write_table(TableData table[], int n, char *filepath);
int search_table(TableData table[], int key1, char *key2, int lines);
void linear_counting_sort(TableData table[], int n);

#endif
