#include <stdio.h>
#include <stdlib.h>
#include "lab5.h"


void dsuCreate(DSU* dsu, int n) {
    dsu->parent = (int*)malloc(n * sizeof(int));
    if (!dsu->parent) {
        printf("<< Memory allocation error >>\n");
        return;
    };
    for (int i = 0; i < n; i++) dsu->parent[i] = i;
};

int dsuFind(DSU *dsu, int val) {
    if (dsu->parent[val] == val) return val;
    return dsu->parent[val] = dsuFind(dsu, dsu->parent[val]);
};

void dsuUnion(DSU *dsu, int a, int b) {
    int parentA = dsuFind(dsu, a);
    int parentB = dsuFind(dsu, b);

    if (parentA != parentB) dsu->parent[parentB] = parentA;
};
