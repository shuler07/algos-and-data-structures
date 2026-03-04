#include <stdio.h>
#include "lab2.h"

const int MAX_TABLE_LEN = 100;

int main() {
    char *input_filepath = "./input.txt";

    int lines = 100;
    TableData *raw_table = (TableData*)calloc(MAX_TABLE_LEN, sizeof(TableData));
    read_table(raw_table, MAX_TABLE_LEN, input_filepath, &lines);

    TableData table[lines];
    for (int i = 0; i < lines; i++) table[i] = raw_table[i];

    free(raw_table);

    printf("Unsorted:\n");
    for (int i = 0; i < lines; i++) {
        printf("%d. %d-%s: %s\n", i, table[i].number, table[i].string, table[i].value);
    };

    linear_counting_sort(table, lines);

    printf("Sorted\n");
    for (int i = 0; i < lines; i++) {
        printf("%d. %d-%s: %s\n", i, table[i].number, table[i].string, table[i].value);
    };

    char *output_filepath = "./output.txt";
    write_table(table, lines, output_filepath);

    return 0;
};
