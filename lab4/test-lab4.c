#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "lab4.h"


void testTreeFirst() {
    AVLTree tr;
    avlTreeCreate(&tr);
    assert(tr.root == NULL);

    tr.root = avlTreeInsert("a", 1, tr.root);
    tr.root = avlTreeInsert("b", 2, tr.root);
    assert(strcmp(tr.root->key, "a") == 0 && tr.root->value == 1 && tr.root->height == 2);
    assert(tr.root->left == NULL && strcmp(tr.root->right->key, "b") == 0);

    tr.root = avlTreeInsert("c", 3, tr.root);
    tr.root = avlTreeInsert("d", 4, tr.root);
    tr.root = avlTreeInsert("e", 5, tr.root);
    assert(tr.root->height == 3 && strcmp(tr.root->key, "a") != 0);

    tr.root = avlTreeRemove("a", tr.root);
    tr.root = avlTreeRemove("b", tr.root);
    tr.root = avlTreeRemove("c", tr.root);
    assert(tr.root->height == 2);

    tr.root = avlTreeRemove("e", tr.root);
    assert(tr.root->height == 1 && strcmp(tr.root->key, "d") == 0);

    tr.root = avlTreeRemove("d", tr.root);
    assert(tr.root == NULL);
    assert(avlTreeSearch("a", tr.root) == NULL);

    tr.root = avlTreeInsert("mykey", 228, tr.root);
    assert(avlTreeSearch("mykey", tr.root)->value == 228);

    printf("Tests passed for first tree\n");
};

int main() {
    testTreeFirst();

    return 0;
};
