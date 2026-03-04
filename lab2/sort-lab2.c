#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lab2.h"

bool compare_table_data(TableData a, TableData b) {
    // false - a > b, true - a <= b
    if (a.number != b.number) {
        if (a.number < b.number) return true;
        return false;
    };
    if (strcmp(a.string, b.string) <= 0) return true;
    return false;
};

void linear_counting_sort(TableData table[], int n) {
    int *count = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (compare_table_data(table[i], table[j])) count[j]++;
            else count[i]++;
        };
    };

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (count[j] == i) {
                if (i == j) break;
                TableData temp = table[i];
                int temp_count = count[i];
                table[i] = table[j];
                count[i] = i;
                table[j] = temp;
                count[j] = temp_count;
                break;
            };
        };
    };
};
