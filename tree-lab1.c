#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lab1.h"


void tree_init(Tree *tree) {
    tree->root = NULL;
};

bool _tree_add_recursive(Node *node, int parent, int value) {
    if (node->value == parent) {
        if (node->children_count != TREE_MAX_CHILDRENS) {
            Node *new_node = (Node*)malloc(sizeof(Node));
            if (!new_node) {
                printf("Memory error");
                return false;
            };
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
    if (!tree->root) {
        Node *new_node = (Node*)malloc(sizeof(Node));
        if (!new_node) {
            printf("Memory error");
            return false;
        };
        new_node->parent = NULL;
        new_node->value = value;
        new_node->children_count = 0;
        tree->root = new_node;
        return true;
    };

    return _tree_add_recursive(tree->root, parent, value);
};

bool _tree_remove_recursive(Node *node, int value, bool is_found) {
    if (node->value == value) {
        is_found = true;
    };
    for (int i = 0; i < node->children_count; i++) {
        bool result = _tree_remove_recursive(node->children[i], value, is_found);
        if (!is_found && result) {
            return true;  // если текущая вершина - число, которое нужно удалить,
                          // то надо пройти по всем потомкам, если нет - то достаточно найти нужное число у 1 потомка
        };
    };
    if (is_found) {
        Node *parent = node->parent;
        bool is_child_found = false;
        for (int i = 0; i < parent->children_count - 1; i++) {
            if (parent->children[i] == node) {
                is_child_found = true;
            };
            if (is_child_found) {
                parent->children[i] = parent->children[i+1];
            };
        };
        parent->children_count--;
        free(node);
        return true;
    };
    return false;
};

bool tree_remove(Tree *tree, int value) {
    return _tree_remove_recursive(tree->root, value, false);
};

void _tree_print_recursive(Node *node, int space, int space_increment) {
    for (int i = 0; i < space; i++) {
        printf(" ");
    };
    printf("%d\n", node->value);
    for (int i = 0; i < node->children_count; i++) {
        _tree_print_recursive(node->children[i], space + space_increment, space_increment);
    };
};

void tree_print(Tree *tree, int space_increment) {
    _tree_print_recursive(tree->root, 0, space_increment);
};

int _tree_peaks_recursive(Node *node) {
    if (node->children_count == 0) {
        return 1;
    };
    int count = 0;
    for (int i = 0; i < node->children_count; i++) {
        count += _tree_peaks_recursive(node->children[i]);
    };
    return count;
};

int tree_peaks(Tree *tree) {
    return _tree_peaks_recursive(tree->root);
};
