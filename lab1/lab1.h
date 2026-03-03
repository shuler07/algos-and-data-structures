#ifndef lab1_h
#define lab1_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

const int TREE_MAX_CHILDRENS = 5;

typedef struct Node {
    Node *parent;
    Node *children[TREE_MAX_CHILDRENS];
    int children_count;
    int value;
} Node;

typedef struct {
    Node *root;
} Tree;

void tree_init(Tree* tree);
bool tree_add(Tree *tree, int parent, int value);
bool tree_remove(Tree *tree, int value);
void tree_print(Tree *tree, int space_increment);
int tree_peaks(Tree *tree);

#endif
