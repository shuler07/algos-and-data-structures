#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lab1.h"


void show_menu_message() {
    printf("\n==============================\n");
    printf("0. Exit program\n");
    printf("1. Add element to tree\n");
    printf("2. Remove element from tree\n");
    printf("3. Print tree\n");
    printf("4. Count tree peaks\n");
    printf("==============================\n");
    printf("Select option: ");
};

void prepare_tree_add_elem(Tree *tree) {
    int parent, value;
    printf("Parent: ");
    scanf(" %d", &parent);
    printf("Value: ");
    scanf(" %d", &value);
    if (tree_add(tree, parent, value)) {
        printf("Added successfully\n");
    };
};

void prepare_tree_remove_elem(Tree *tree) {
    int value;
    printf("Value: ");
    scanf(" %d", &value);
    if (tree_remove(tree, value)) {
        printf("Removed successfully\n");
    };
}

void prepare_tree_print(Tree *tree) {
    int space_increment;
    printf("Space increment: ");
    scanf(" %d", &space_increment);
    tree_print(tree, space_increment);
};

void prepare_tree_peaks(Tree *tree) {
    int peaks = tree_peaks(tree);
    printf("Peaks: %d\n", peaks);
};

void warning_message(char cmd) {
    printf("Unknown command: %c\n", cmd);
    printf("Allowed commands: 0, 1, 2, 3, 4\n");
};

int main() {
    Tree tree;

    printf("Root value: ");
    int root_value;
    scanf(" %d", &root_value);
    tree_init(&tree, root_value);

    bool is_program_working = true;
    while (is_program_working) {
        show_menu_message();

        char choice;
        scanf(" %c", &choice);
        printf("\n");

        switch (choice) {
            case '0':
                is_program_working = false;
                break;
            case '1':
                prepare_tree_add_elem(&tree);
                break;
            case '2':
                prepare_tree_remove_elem(&tree);
                break;
            case '3':
                prepare_tree_print(&tree);
                break;
            case '4':
                prepare_tree_peaks(&tree);
                break;
            default:
                warning_message(choice);
                break;
        };
    };

    return 0;
};
