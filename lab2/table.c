#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "lab2.h"

char *readline(FILE *file) {
    int i = 0, buf_size = 8;
    char *buf = (char*)malloc(buf_size);
    char ch;
    while ((ch = fgetc(file)) != '\n' && ch != '\r' && ch != EOF) {
        buf[i++] = ch;
        if (i == buf_size - 1) {
            buf_size *= 2;
            char *new_buf = (char*)realloc(buf, buf_size);
            if (!new_buf) {
                free(buf);
                return NULL;
            };
            buf = new_buf;
        };
    };
    if (ch == '\r') fgetc(file);
    buf[i] = '\0';
    return buf;
};

bool read_table(TableData table[], int table_limit, char *filepath, int *lines) {
    FILE *input_table;
    input_table = fopen(filepath, "r");

    if (!input_table) {
        printf("Error when reading file: %s\n", filepath);
        return false;
    };

    int n;
    fscanf(input_table, "%d ", &n);
    *lines = n;

    if (n > table_limit) {
        printf("Table bigger than expected");
        fclose(input_table);
        return false;
    };

    for (int i = 0; i < n; i++) {
        fscanf(input_table, "%d ", &table[i].number);
        char *key_string = readline(input_table);
        if (!key_string) printf("WARNING: memory allocation error on %d line\n", (i + 1) * 2);
        table[i].string = key_string;
        char *value_string = readline(input_table);
        if (!value_string) printf("WARNING: memory allocation error on %d line\n", (i + 1) * 2 + 1);
        table[i].value = value_string;
    };

    fclose(input_table);
    return true;
};

bool write_table(TableData table[], int n, char *filepath) {
    FILE *output_table;
    output_table = fopen(filepath, "w");

    if (!output_table) {
        printf("Error when writing file: %s\n", filepath);
        return false;
    };

    char n_str[16];
    sprintf(n_str, "%d\n", n);

    fputs(n_str, output_table);

    for (int i = 0; i < n; i++) {
        fprintf(output_table, "%d %s\n", table[i].number, table[i].string);
        fprintf(output_table, "%s\n", table[i].value);
    };

    fclose(output_table);
    return true;
};

int search_table(TableData table[], int key1, char *key2, int lines) {
    for (int i = 0; i < lines; i++) {
        if (table[i].number == key1 && strcmp(table[i].string, key2) == 0) {
            return i;
        };
    };
    return -1;
};
