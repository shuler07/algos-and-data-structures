#include <stdio.h>
#include <stdbool.h>
#include "lab3.h"


void show_system_message(bool is_expr_entered) {
    printf("[ Expression not entered ]\n");
    printf("[ 1 ] Enter expression\n");
    printf("[ 2 ] Print expression\n");
    printf("[ 3 ] Print postfix expression\n");
    printf("[ 4 ] Print expression as tree\n");
    printf("[ 5 ] Remove unary minuses from multiplies\n");
    printf("[ 0 ] Exit program\n");
};

int main() {
    int expr_size;
    bool is_expr_entered = false;

    char *expr = NULL;
    char *postfix_expr;
    Tree expr_tree;
    tree_create(&expr_tree);

    while (true) {
        int choice;
        show_system_message(is_expr_entered);
        scanf("%d ", &choice);
        switch (choice) {
            case 0: return 0;
            case 1:
                printf(" => Type expression: ");
                expr = get_expr_string(&expr_size);
                if (expr[0] == '\0') printf("<< Empty expression! >>\n");
                else {
                    is_expr_entered = true;
                    postfix_expr = get_postfix_expr(expr, expr_size);
                    postfix_expr_to_tree(postfix_expr, &expr_tree);
                };
                break;
            case 2:
                if (!is_expr_entered) printf("<< Enter expression first! >>\n");
                else printf(" => Expression: %s\n", expr);
                break;
            case 3:
                if (!is_expr_entered) printf("<< Enter expression first! >>\n");
                else printf(" => Postfix expression: %s\n", postfix_expr);
                break;
            case 4:
                if (!is_expr_entered) printf("<< Enter expression first! >>\n");
                else tree_print(expr_tree.root, 0);
                break;
            case 5:
                if (!is_expr_entered) printf("<< Enter expression first! >>\n");
                else {
                    tree_remove_unary_minuses(&expr_tree, expr_tree.root);
                    expr = tree_to_expr(expr_tree.root, expr_size);
                    postfix_expr = get_postfix_expr(expr, expr_size);
                };
                break;
            };
    };

    return 0;
};
