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

    // Потомки правого потомка
    if (tree_add_rec(node->right, val)) return true;

    // Унарный минус / плюс может иметь только одного потомка - правого
    if (node->val[0] == '~' || node->val[0] == '$') return false;

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

void tree_remove_unary_minuses(TreeNode *node) {
    if (node->val[0] == '*') {
        TreeNode *lchild = node->left, *rchild = node->right;
        if (lchild->val[0] == '~' && rchild->val[0] == '~') {
            node->left = lchild->right;
            node->right = rchild->right;
            node->left->parent = node;
            node->right->parent = node;
            free(lchild);
            free(rchild);
        } else if (lchild->val[0] == '~') {
            TreeNode *mul_node = (TreeNode*)malloc(sizeof(TreeNode));
            mul_node->val = node->val;
            mul_node->parent = node;
            mul_node->left = lchild->right;
            mul_node->right = rchild;
            node->val = lchild->val;
            node->left = NULL;
            node->right = mul_node;
            free(lchild);
        } else if (rchild->val[0] == '~') {
            TreeNode *mul_node = (TreeNode*)malloc(sizeof(TreeNode));
            mul_node->val = node->val;
            mul_node->parent = node;
            mul_node->left = lchild;
            mul_node->right = rchild->right;
            node->val = rchild->val;
            node->left = NULL;
            node->right = mul_node;
            free(rchild);
        };
    };
    if (node->left) tree_remove_unary_minuses(node->left);
    if (node->right) tree_remove_unary_minuses(node->right);
};
