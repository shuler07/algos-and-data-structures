#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab3.h"


void postfix_expr_to_tree(List *tokens, Tree *tr) {
    ListNode *cur = tokens->last;
    while (cur) {
        tree_add(tr, cur->token);
        cur = cur->prev;
    };
};

char *tree_to_expr(TreeNode *node, int expr_size) {
    char *res = (char*)calloc(expr_size, 1);

    if (node->left) strcat(res, tree_to_expr(node->left, expr_size));

    // Если унарный минус - есть только левое поддерево
    if (node->val[0] == '~') {
        res[0] = '-';
        res[1] = '(';
        strcat(res, tree_to_expr(node->right, expr_size));
        res[strlen(res)] = ')';
        return res;
    };
    
    strcat(res, node->val);
    if (node->right) strcat(res, tree_to_expr(node->right, expr_size));

    return res;
};
