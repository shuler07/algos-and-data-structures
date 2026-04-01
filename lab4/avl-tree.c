#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lab4.h"


int getHeight(Node *root) {
    return root ? root->height : 0;
};

int bFactor(Node *root) {
    return getHeight(root->right) - getHeight(root->left);
};

void fixHeight(Node *root) {
    int l = getHeight(root->left), r = getHeight(root->right);
    root->height = 1 + (l >= r ? l : r);
}

Node *rotateRight(Node *p) {
    Node *q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
};

Node *rotateLeft(Node *q) {
    Node *p = q->right;
    q->right = p->left;
    p->left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
};

Node *balance(Node *p) {
    fixHeight(p);
    if (bFactor(p) == -2) {
        if (bFactor(p->left) > 0) p->left = rotateLeft(p->left);
        return rotateRight(p);
    };
    if (bFactor(p) == 2) {
        if (bFactor(p->right) < 0) p->right = rotateRight(p->right);
        return rotateLeft(p);
    };
    return p;
};

Node *findMin(Node *p) {
    if (p->left) return findMin(p->left);
    return p;
};

Node *removeMin(Node *p) {
    if (!p->left) return p->right;
    p->left = removeMin(p->left);
    return balance(p);
};



void avlTreeCreate(AVLTree *tr) {
    tr->root = NULL;
};

Node *avlTreeInsert(char key[7], double value, Node *root) {
    // создание ноды
    if (!root) {
        Node *node = (Node*)malloc(sizeof(Node));
        if (!node) {
            printf("<< Memory allocation error >>\n");
            return root;
        };
        strcpy(node->key, key);
        node->value = value;
        node->left = node->right = NULL;
        node->height = 1;
        return node;
    };
    
    int comp = strcmp(key, root->key);
    if (comp < 0) root->left = avlTreeInsert(key, value, root->left);
    else if (comp > 0) root->right = avlTreeInsert(key, value, root->right);
    else printf("<< Key %s already exists >>\n", key);

    return balance(root);
};

Node *avlTreeRemove(char key[7], Node *root) {
    if (!root) return root;

    int comp = strcmp(key, root->key);
    if (comp < 0) root->left = avlTreeRemove(key, root->left);
    else if (comp > 0) root->right = avlTreeRemove(key, root->right);
    else {
        Node *l = root->left, *r = root->right;
        free(root);
        if (!r) return l;
        Node *min = findMin(r);
        min->right = removeMin(r);
        min->left = l;
        return balance(min);
    };

    return balance(root);
};

Node *avlTreeSearch(char key[7], Node *root) {
    if (!root) return root;

    int comp = strcmp(key, root->key);
    if (comp < 0) return avlTreeSearch(key, root->left);
    else if (comp > 0) return avlTreeSearch(key, root->right);
    else return root;
};

void avlTreePrint(Node *root, int space) {
    if (!root) return;
    if (space == 0) printf(" => AVLTree:\n");
    for (int i = 0; i < space; i++) printf(" ");
    printf("%s: %.2lf\n", root->key, root->value);
    if (root->left) avlTreePrint(root->left, space + 2);
    if (root->right) avlTreePrint(root->right, space + 2);
};
