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

void tree_remove_unary_minuses(TreeNode *node, Tree *tr) {
    printf("checking %c\n", node->val[0]);
    if (node->val[0] == '*') {
        printf("* in node\n");
        TreeNode *lchild = node->left, *rchild = node->right;
        if (lchild->val[0] == '~' && rchild->val[0] == '~') {
            node->left = lchild->right;
            node->right = rchild->right;
            node->left->parent = node;
            node->right->parent = node;
            free(lchild);
            free(rchild);

            printf("\n\n");
            tree_print(tr->root, 0);
            printf("\n\n");
            printf("executing recursive for children\n");
            if (node->left) tree_remove_unary_minuses(node->left, tr);
            if (node->right) tree_remove_unary_minuses(node->right, tr);
        } else if (lchild->val[0] == '~') {
            printf("~ in left child\n");
            TreeNode *mul_node = (TreeNode*)malloc(sizeof(TreeNode));
            mul_node->val = node->val;
            mul_node->parent = node;
            mul_node->left = lchild->right;
            mul_node->right = rchild;
            TreeNode *parent = node->parent;
            if (parent) {
                printf("has parent\n");
                if (parent->val[0] == '~') {
                    printf("~ in parent\n");
                    if (parent->parent) {
                        printf("parent has parent\n");
                        if (parent->parent->left == parent) { parent->parent->left = mul_node; printf("parent->parent left now mul_node\n"); }
                        else { parent->parent->right = mul_node; printf("parent->parent right now mul_node\n"); }
                    } else {
                        printf("parent has no parent\n");
                        mul_node->parent = NULL;
                        tr->root = mul_node;
                        printf("root now mul_node\n");
                    }
                    printf("clearing parent, node...\n");
                    free(parent);
                    free(node);
                    printf("parent, node cleared\n");
                } else {
                    printf("has no parent\n");
                    node->val = lchild->val;
                    node->left = NULL;
                    node->right = mul_node;
                    free(lchild);
                    printf("executing recursive for parent\n");
                    tree_remove_unary_minuses(parent, tr);
                };
            };
            printf("\n\n");
            tree_print(tr->root, 0);
            printf("\n\n");
            printf("executing recursive for children\n");
            if (mul_node->left) tree_remove_unary_minuses(mul_node->left, tr);
            if (mul_node->right) tree_remove_unary_minuses(mul_node->right, tr);
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
            if (node->parent) tree_remove_unary_minuses(node->parent, tr);
        };
    } else {
        printf("\n\n");
        tree_print(tr->root, 0);
        printf("\n\n");
        printf("executing recursive for children\n");
        if (node->left) tree_remove_unary_minuses(node->left, tr);
        if (node->right) tree_remove_unary_minuses(node->right, tr);
    };
};
