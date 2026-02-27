#include <stdio.h>
#include <stdbool.h>
#include "lab1.h"


bool test_tree_count_peaks(Tree *tree) {
    int peaks = tree_peaks(tree);

    if (peaks == 0) {
        tree_add(tree, 1, 1);
        tree_add(tree, 1, 2);
        tree_add(tree, 1, 3);
        tree_add(tree, 1, 4);
        tree_add(tree, 2, 5);
        tree_add(tree, 2, 6);

        peaks = tree_peaks(tree);
        if (peaks == 4) {
            printf("Peaks counted correct\n");
            return true;
        };

        printf("Error when counting peaks #2\n");
    };

    printf("Error when counting peaks #1\n");
    return false;
};

bool test_tree_remove_root(Tree *tree) {
    tree_remove(tree, 1);

    if (!tree->root) {
        printf("Root removed successfully\n");
        return test_tree_count_peaks(tree);
    };

    printf("Error when removing root\n");
    return false;
};

bool test_tree_remove_elements(Tree *tree) {
    tree_remove(tree, 4);
    tree_remove(tree, 3);
    
    if (tree->root->children_count == 1) {
        printf("Elements removed successfully\n");
        return test_tree_remove_root(tree);
    };

    printf("Error when removing elements\n");
    return false;
};

bool test_tree_add_elements(Tree *tree) {
    tree_add(tree, 1, 1);  // Creating root element = 1
    tree_add(tree, 1, 2);
    tree_add(tree, 1, 3);
    tree_add(tree, 1, 4);

    if (tree->root && tree->root->value == 1 && tree->root->children_count == 3) {
        Node *root = tree->root;
        if (root->children[0]->value == 2 && root->children[1]->value == 3 && root->children[2]->value == 4) {
            printf("Elements added successfully\n");
            return test_tree_remove_elements(tree);
        };

        printf("Error when adding elements #2\n");
    };

    printf("Error when adding elements #1\n");
    return false;
};

bool test_tree() {
    Tree tree;
    tree_init(&tree);
    if (!tree.root) {
        printf("Tree created successfully\n");
        return test_tree_add_elements(&tree);
    };

    printf("Error when creating tree\n");
    return false;
};

int main() {
    bool test_result = test_tree();

    if (test_result) {
        printf("\nAll tests passed successfully!\n");
    };

    return 0;
};
