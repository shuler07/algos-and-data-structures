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



void tree_init(Tree *tree, int value) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->parent = NULL;
    node->children_count = 0;
    node->value = value;
    tree->root = node;
    return;
};

bool _tree_add_recursive(Node *node, int parent, int value) {
    if (node->value == parent) {
        if (node->children_count != TREE_MAX_CHILDRENS) {
            Node *new_node = (Node*)malloc(sizeof(Node));
            new_node->parent = node;
            new_node->value = value;
            node->children[node->children_count] = new_node;
            node->children_count++;
            return true;
        };
    };
    for (int i = 0; i < node->children_count; i++) {
        if (_tree_add_recursive(node->children[i], parent, value)) {
            return true;
        };
    };
    return false;
};

bool tree_add(Tree *tree, int parent, int value) {
    return _tree_add_recursive(tree->root, parent, value);
};

void tree_remove(Tree *tree, int value) {

};

void _tree_print_recursive(Node *node, int space, int space_increment) {
    for (int i = 0; i < space; i++) {
        printf(" ");
    };
    printf("%d\n", node->value);
    for (int i = 0; i < node->children_count; i++) {
        _tree_print_recursive(node->children[i], space + space_increment, space_increment);
    };
    return;
};

void tree_print(Tree *tree, int space_increment) {
    _tree_print_recursive(tree->root, 0, space_increment);
};

void tree_peaks(Tree *tree) {

};



void show_menu_message() {
    printf("\n==============================\n");
    printf("0. Exit program\n");
    printf("1. Add element to tree\n");
    printf("2. Remove element from tree\n");
    printf("3. Print tree\n");
    printf("4. Count tree peaks\n");
    printf("==============================\n");
    printf("Select option: ");
    return;
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
                int parent, value;
                printf("Parent: ");
                scanf(" %d", &parent);
                printf("Value: ");
                scanf(" %d", &value);
                if (tree_add(&tree, parent, value)) {
                    printf("Added successfully\n");
                };
                break;
            case '2':
                break;
            case '3':
                int space_increment;
                printf("Space increment: ");
                scanf(" %d", &space_increment);
                tree_print(&tree, space_increment);
                break;
            case '4':
                break;
            default:
                break;
        };
    };

    return 0;
};
