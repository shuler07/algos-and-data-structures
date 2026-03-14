#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab3.h"


void postfix_expr_to_tree(char *expr, Tree *tr) {
    int ind = strchr(expr, '\0') - expr;
    for (int i = ind - 1; i >= 0; i--) tree_add(tr, expr[i]);
};

char *tree_to_expr(TreeNode *node, int expr_size) {
    char *res = (char*)calloc(expr_size, 1);

    if (node->left) strcat(res, tree_to_expr(node->left, expr_size));

    // Если унарный минус - есть только левое поддерево
    if (node->val == '~') {
        res[0] = '-';
        res[1] = '(';
        strcat(res, tree_to_expr(node->right, expr_size));
        res[strlen(res)] = ')';
        return res;
    };
    
    res[strlen(res)] = node->val;
    if (node->right) strcat(res, tree_to_expr(node->right, expr_size));

    return res;
};
