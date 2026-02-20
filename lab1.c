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
