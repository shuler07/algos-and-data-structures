#ifndef LAB5_H
#define LAB5_H

#include <stdbool.h>

// dsu.c
typedef struct {
    int *parent;
} DSU;

void dsuCreate(DSU* dsu, int n);
int dsuFind(DSU *dsu, int val);
void dsuUnion(DSU *dsu, int a, int b);

// list.c
typedef struct Node {
    int a;
    int b;
    int len;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *root;
} List;

void listCreate(List *lst);
void listAdd(List *lst, int a, int b, int len);

// graph.c
typedef struct {
    int n_vertices;
    int n_edges;
    int *matrix;
    List *edges;
} Graph;

bool graphCreate(Graph *gr, int n);
void graphAddEdge(Graph *gr, int a, int b, int len);
void graphPrint(Graph *gr);
Graph graphKruskal(Graph *gr);

#endif
