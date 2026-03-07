#include <stdio.h>
#include <stdbool.h>
#include "lab2.h"

const int MAX_TABLE_LEN = 100;

void show_cli_message(bool is_table_loaded, int lines) {
    if (is_table_loaded) printf("(Table loaded, %d lines) ", lines);
    else printf("(Table not loaded) ");
    printf("Choose option:\n");
    printf("1. Load table\n");
    printf("2. Print table\n");
    printf("3. Sort table\n");
    printf("4. Find value in table\n");
    printf("5. Save table\n");
    printf("0. Exit program\n");
};

void try_load_table(TableData table[], int *lines, bool *is_table_loaded) {
    char table_path[128];
    printf("Path: ");
    scanf("%s", table_path);
    if (read_table(table, MAX_TABLE_LEN, table_path, lines)) *is_table_loaded = true;
};

void print_table(TableData table[], int lines) {
    for (int i = 0; i < lines; i++) {
        printf("%d. %d-%s: %s\n", i, table[i].number, table[i].string, table[i].value);
    };
};

void try_search_table(TableData table[], int lines) {
    int key1;
    char key2[128];
    printf("Key in format <number string>: ");
    scanf("%d %s", &key1, key2);
    search_table(table, key1, key2, lines);
};

void try_save_table(TableData table[], int lines) {
    char table_path[128];
    printf("Path: ");
    scanf("%s", table_path);
    if (write_table(table, lines, table_path)) printf("Table saved successfully\n");
};

int main() {
    int lines = MAX_TABLE_LEN;
    TableData *table = (TableData*)calloc(lines, sizeof(TableData));
    bool is_table_loaded = false;

    while (true) {
        show_cli_message(is_table_loaded, lines);
        int option;
        scanf("%d", &option);
        switch (option) {
            case 0:
                return 0;
            case 1:
                try_load_table(table, &lines, &is_table_loaded);
                break;
            case 2:
                if (is_table_loaded) print_table(table, lines);
                else printf("Table not loaded!\n");
                break;
            case 3:
                if (is_table_loaded) linear_counting_sort(table, lines);
                else printf("Table not loaded!\n");
                break;
            case 4:
                if (is_table_loaded) try_search_table(table, lines);
                else printf("Table not loaded!\n");
                break;
            case 5:
                if (is_table_loaded) try_save_table(table, lines);
                else printf("Table not loaded!\n");
                break;
        };
    };

    return 0;
};
