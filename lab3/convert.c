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
    char *res = (char*)malloc(expr_size);
    res[0] = '\0';

    int priority = oper_priority(node->val[0]);
    
    // Вершина дерева - число
    if (priority == -1) return strcat(res, node->val);

    // Левое выражение
    if (node->left) {
        int lpriority = oper_priority(node->left->val[0]);
        if (lpriority == -1) strcat(res, node->left->val);
        else {
            if (lpriority < priority) strcat(res, "(");
            strcat(res, tree_to_expr(node->left, expr_size));
            if (lpriority < priority) strcat(res, ")");
        };
    };

    // Обработка знака
    if (priority == 5) {
        if (node->val[0] == '~') strcat(res, "-");
        else strcat(res, "+");
    } else strcat(res, node->val);
    
    // Правое выражение
    if (node->right) {
        int rpriority = oper_priority(node->right->val[0]);
        if (rpriority == -1) strcat(res, node->right->val);
        else {
            if (rpriority < priority) strcat(res, "(");
            strcat(res, tree_to_expr(node->right, expr_size));
            if (rpriority < priority) strcat(res, ")");
        };
    };

    return res;
};
