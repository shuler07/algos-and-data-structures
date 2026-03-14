#include <stdio.h>
#include "lab3.h"


void process_expr(char *expr, int expr_size) {
    char *postfix_expr = get_postfix_expr(expr, expr_size);
    printf(" - Postfix expression: %s\n", postfix_expr);

    Tree tree_expr;
    tree_create(&tree_expr);
    postfix_expr_to_tree(postfix_expr, &tree_expr);
    printf(" - Tree:\n");
    tree_print(tree_expr.root, 0);

    tree_remove_unary_minuses(&tree_expr, tree_expr.root);
    printf(" - Tree after removing unary minuses:\n");
    tree_print(tree_expr.root, 0);

    char *final_expr = tree_to_expr(tree_expr.root, expr_size);
    printf(" - Final expression: %s\n", final_expr);
};

int main() {
    int expr_size;
    char *expr;

    while (1) {
        printf("(0 - Exit program)\nType expression: ");
        expr = get_string(&expr_size);
        if (expr[0] == '0' && expr[1] == '\0') return 0;
        if (expr[0] == '\0') continue;
        process_expr(expr, expr_size);
    };

    return 0;
};
