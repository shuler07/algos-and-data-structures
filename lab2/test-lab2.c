#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "lab2.h"

void random_key_string(char buffer[]) {
    int letters = rand() % 50 + 5;
    for (int i = 0; i < letters; i++) {
        buffer[i] = (char)(rand() % 26 + 97);
    };
    buffer[letters] = '\0';
};

void test_table_sort(TableData table[], int n) {
    printf("testing sorting of table size = %d\n", n);
    linear_counting_sort(table, n);
    
    for (int i = 1; i < n; i++) {
        assert(table[i-1].number <= table[i].number);
        if (table[i-1].value == table[i].value) {
            assert(strcmp(table[i-1].string, table[i].string) == -1);
        };
    };
};

void test_table_io() {
    for (int size = 10; size <= 30; size += 10) {
        printf("testing size = %d\n", size);
        TableData *test_table = (TableData*)calloc(size, sizeof(TableData));
        for (int i = 0; i < size; i++) {
            test_table[i].number = rand();
            random_key_string(test_table[i].string);
            random_key_string(test_table[i].value);
        };
        printf("table filled\n");

        char table_filename[20] = "./test-table.txt";
        write_table(test_table, size, table_filename);
        printf("table written\n");
        
        TableData *check_table = (TableData*)calloc(size, sizeof(TableData));
        read_table(check_table, size, table_filename, &size);
        printf("table read");

        for (int i = 0; i < size; i++) {
            assert(test_table[i].number == check_table[i].number);
            assert(strcmp(test_table[i].string, check_table[i].string) == 0);
            assert(strcmp(test_table[i].value, check_table[i].value) == 0);
        };

        free(check_table);
        test_table_sort(test_table, size);
        free(test_table);
    };
};

int main() {
    srand(time(NULL));

    test_table_io();
    printf("Tests passed\n");

    return 0;
};
