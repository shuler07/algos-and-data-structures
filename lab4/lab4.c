#include <stdio.h>
#include <stdbool.h>
#include "lab4.h"


void showSystemMessage() {
    printf("AVL Tree\n");
    printf("[1] Insert node\n");
    printf("[2] Remove node\n");
    printf("[3] Search key\n");
    printf("[4] Print tree\n");
    printf("[0] Exit program\n");
};

bool prepareInsertNode(AVLTree *tr) {
    char key[7];
    printf(" => Type key: ");
    scanf("%s", key);
    double value;
    printf(" => Type value: ");
    scanf("%lf", &value);
    tr->root = avlTreeInsert(key, value, tr->root);
};

void prepareRemoveNode(AVLTree *tr) {
    char key[7];
    printf(" => Type key: ");
    scanf("%s", key);
    tr->root = avlTreeRemove(key, tr->root);
};

void prepareSearchKey(AVLTree *tr) {
    char key[7];
    printf(" => Type key: ");
    scanf("%s", key);
    Node *found = avlTreeSearch(key, tr->root);
    if (found) printf("Found\n%s: %.2lf\n", found->key, found->value);
    else printf("Key not found\n");
};

int main() {
    AVLTree tree;
    avlTreeCreate(&tree);
    
    int option;
    while (true) {
        showSystemMessage();
        scanf("%d", &option);
        switch (option) {
            case 0:
                return 0;
            case 1:
                prepareInsertNode(&tree);
                break;
            case 2:
                prepareRemoveNode(&tree);
                break;
            case 3:
                prepareSearchKey(&tree);
                break;
            case 4:
                avlTreePrint(tree.root, 0);
                break;
            default:
                printf("<< Unknown command: %d >>\n", option);
                break;
        };
    };

    return 0;
};
