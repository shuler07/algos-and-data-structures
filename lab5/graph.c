#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lab5.h"


bool graphCreate(Graph *gr, int n) {
    if (n <= 1) {
        printf("<< Vertices count must be positive integer greather than 1 >>\n");
        return false;
    };
    gr->n_vertices = n;
    gr->n_edges = 0;
    gr->matrix = (int*)calloc(n * n, sizeof(int));
    if (!gr->matrix) {
        printf("<< Memory allocation error >>\n");
        return false;
    };
    gr->edges = (List*)malloc(sizeof(List));
    listCreate(gr->edges);
    return true;
};

void graphAddEdge(Graph *gr, int a, int b, int len) {
    if (a < 0 || b < 0) {
        printf("<< Vertices must be non negative integers >>\n");
        return;
    };
    if (a == b) {
        printf("<< Attempt to add a degenerate edge! >>\n");
        return;
    };
    if (len <= 0) {
        printf("<< Edge length must be positive integer >>\n");
        return;
    };
    int n = gr->n_vertices;
    if (gr->matrix[a * n + b] != 0) {
        printf("<< Edge between %d and %d already axists >>\n", a, b);
        return;
    };
    gr->matrix[a * n + b] = len;
    gr->matrix[b * n + a] = len;
    gr->n_edges++;
    listAdd(gr->edges, a, b, len);
};

void graphPrint(Graph *gr) {
    int n = gr->n_vertices;

    printf("    ");
    for (int i = 0; i < n; i++) printf("%3d ", i);

    for (int i = 0; i < n; i++) {
        printf("\n%3d ", i);
        for (int j = 0; j < n; j++) printf("%3d ", gr->matrix[i * n + j]);
    };

    printf("\n");
};

Graph graphKruskal(Graph *gr) {
    Graph result;
    graphCreate(&result, gr->n_vertices);

    DSU dsu;
    dsuCreate(&dsu, gr->n_vertices);

    Node *cur = gr->edges->root;
    while (cur) {
        int a = cur->a, b = cur->b, len = cur->len;
        if (dsuFind(&dsu, a) != dsuFind(&dsu, b)) {
            dsuUnion(&dsu, a, b);
            graphAddEdge(&result, a, b, len);
        };
        if (result.n_edges == gr->n_vertices) break;
        cur = cur->next;
    };

    free(dsu.parent);

    return result;
};
