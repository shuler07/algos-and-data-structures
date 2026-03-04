#ifndef lab2_h
#define lab2_h

#include <stdlib.h>

const int MAX_KEY_LEN = 128;
const int MAX_VALUE_LEN = 128;

typedef struct {
    int number;
    char string[MAX_KEY_LEN];
    char value[MAX_VALUE_LEN];
} TableData;

void read_table(TableData table[], int table_limit, char *filepath, int *lines);
void write_table(TableData table[], int n, char *filepath);
void linear_counting_sort(TableData table[], int n);

#endif
