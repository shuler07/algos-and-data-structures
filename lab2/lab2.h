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

bool read_table(TableData table[], int table_limit, char *filepath, int *lines);
bool write_table(TableData table[], int n, char *filepath);
void search_table(TableData table[], int key1, char key2[128], int lines);
void linear_counting_sort(TableData table[], int n);

#endif
