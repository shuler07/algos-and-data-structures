#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lab2.h"

void read_table(TableData table[], int table_limit, char *filepath, int *lines) {
    FILE *input_table;
    input_table = fopen(filepath, "r");

    if (!input_table) {
        printf("Error when reading file: %s\n", filepath);
        return;
    };

    int n;
    fscanf(input_table, "%d ", &n);
    *lines = n;

    if (n > table_limit) {
        printf("Table bigger than expected");
        fclose(input_table);
        return;
    };

    for (int i = 0; i < n; i++) {
        if (fscanf(input_table, "%d %s ", &table[i].number, table[i].string) == 2) {
            fgets(table[i].value, sizeof(table[i].value), input_table);
            table[i].value[strcspn(table[i].value, "\n\r")] = '\0';
        };
    };

    fclose(input_table);
};

void write_table(TableData table[], int n, char *filepath) {
    FILE *output_table;
    output_table = fopen(filepath, "w");

    if (!output_table) {
        printf("Error when writing file: %s\n", filepath);
        return;
    };

    char n_str[10];
    sprintf(n_str, "%d\n", n);

    fputs(n_str, output_table);

    for (int i = 0; i < n; i++) {
        char key_str[MAX_KEY_LEN + 12];
        sprintf(key_str, "%d %s\n", table[i].number, table[i].string);
        fputs(key_str, output_table);
        char value_str[MAX_VALUE_LEN + 1];
        sprintf(value_str, "%s\n", table[i].value);
        fputs(value_str, output_table);
    };

    fclose(output_table);
};
