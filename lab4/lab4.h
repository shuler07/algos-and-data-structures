#ifndef lab4_h
#define lab4_h

// avl-tree.c
typedef struct Node {
    char key[7];
    double value;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    Node *root;
} AVLTree;

void avlTreeCreate(AVLTree *tr);
Node *avlTreeInsert(char key[7], double value, Node *root);
Node *avlTreeRemove(char key[7], Node *root);
void avlTreePrint(Node *root, int space);

#endif
