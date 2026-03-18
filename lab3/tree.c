#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lab3.h"


void tree_create(Tree *tr) {
    tr->root = NULL;
};

void tree_clear_rec(TreeNode *node) {
    if (node->left) tree_clear_rec(node->left);
    if (node->right) tree_clear_rec(node->right);
    free(node);
};

void tree_clear(Tree *tr) {
    tree_clear_rec(tr->root);
    tree_create(tr);
};

bool tree_add_rec(TreeNode *node, char *val) {
    if ('0' <= node->val[0] && node->val[0] <= '9') return false;
    if ('a' <= node->val[0] && node->val[0] <= 'z') return false;
    if ('A' <= node->val[0] && node->val[0] <= 'Z') return false;
    
    // Правый потомок
    if (!node->right) {
        TreeNode *new_node = (TreeNode*)malloc(sizeof(TreeNode));
        if (!new_node) {
            printf("<< Memory allocation error! >>\n");
            return false;
        };
        new_node->val = val;
        new_node->parent = node;
        new_node->left = new_node->right = NULL;
        node->right = new_node;
        return true;
    };

    // Унарный минус может иметь только одного потомка - правого
    if (node->val[0] == '~') return false;

    // Потомки правого потомка
    if (tree_add_rec(node->right, val)) return true;

    // Левый потомок
    if (!node->left) {
        TreeNode *new_node = (TreeNode*)malloc(sizeof(TreeNode));
        if (!new_node) {
            printf("<< Memory allocation error! >>\n");
            return false;
        };
        new_node->val = val;
        new_node->parent = node;
        new_node->left = new_node->right = NULL;
        node->left = new_node;
        return true;
    };

    // Потомки левого потомка
    if (tree_add_rec(node->left, val)) return true;

    return false;
};

void tree_add(Tree *tr, char *val) {
    if (!tr->root) {
        TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
        if (!node) {
            printf("<< Memory allocation error! >>\n");
            return;
        };
        node->val = val;
        node->parent = node->left = node->right = NULL;
        tr->root = node;
        return;
    };
    if (!tree_add_rec(tr->root, val)) printf("<< Tree adding error! >>\n");
};

void tree_print(TreeNode *node, int space) {
    if (!space) printf(" => Tree expression:\n");
    for (int i = 0; i < space; i++) printf(" ");
    printf("%s\n", node->val);
    if (node->left) tree_print(node->left, space + 2);
    if (node->right) tree_print(node->right, space + 2);
};

void tree_remove_unary_minuses(Tree *tr, TreeNode *node) {
    if (node->val[0] == '~') {
        if (tr->root == node) return;
        TreeNode *child = node->right;
        node->val = child->val;
        node->right = NULL;
        free(child);
        if (tr->root->val[0] == '~') {
            TreeNode *old_root = tr->root;
            tr->root = tr->root->right;
            tr->root->parent = NULL;
            free(old_root);
        } else {
            TreeNode *new_root = (TreeNode*)malloc(sizeof(TreeNode));
            new_root->val[0] = '~';
            new_root->parent = new_root->left = NULL;
            new_root->right = tr->root;
            tr->root = new_root;
        };
    };
    if (node->left) tree_remove_unary_minuses(tr, node->left);
    if (node->right) tree_remove_unary_minuses(tr, node->right);
};
