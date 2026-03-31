#include <stdio.h>
#include <stdbool.h>
#include "lab3.h"


void show_system_message(bool is_expr_entered) {
    if (is_expr_entered) printf("\n[ Expression entered ]\n");
    else printf("\n[ Expression not entered ]\n");
    printf("[ 1 ] Enter expression\n");
    printf("[ 2 ] Print expression\n");
    printf("[ 3 ] Print postfix expression\n");
    printf("[ 4 ] Print postfix expression tokens\n");
    printf("[ 5 ] Print expression as tree\n");
    printf("[ 6 ] Remove unary minuses from multiplies\n");
    printf("[ 0 ] Exit program\n");
};

int main() {
    int expr_size;
    bool is_expr_entered = false;

    char *expr = NULL;
    char *postfix_expr;
    
    List expr_tokens;
    list_create(&expr_tokens);

    Tree expr_tree;
    tree_create(&expr_tree);
    char garbage;

    while (true) {
        show_system_message(is_expr_entered);
        int choice;
        scanf("%d%c", &choice, &garbage);
        switch (choice) {
            case 0: return 0;
            case 1:
                printf(" => Type expression: ");
                expr = get_expr_string(&expr_size);
                if (expr[0] == '\0') printf("<< Empty expression! >>\n");
                else {
                    if (is_expr_entered) {
                        list_clear(&expr_tokens);
                        tree_clear(&expr_tree);
                    };
                    is_expr_entered = true;
                    postfix_expr = get_postfix_expr(expr, expr_size, &expr_tokens);
                    postfix_expr_to_tree(&expr_tokens, &expr_tree);
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
                else list_print(&expr_tokens);
                break;
            case 5:
                if (!is_expr_entered) printf("<< Enter expression first! >>\n");
                else tree_print(expr_tree.root, 0);
                break;
            case 6:
                if (!is_expr_entered) printf("<< Enter expression first! >>\n");
                else {
                    tree_remove_unary_minuses(expr_tree.root, &expr_tree);
                    printf("finished!\n");
                    tree_print(expr_tree.root, 0);
                    expr = tree_to_expr(expr_tree.root, expr_size);
                    list_clear(&expr_tokens);
                    postfix_expr = get_postfix_expr(expr, expr_size, &expr_tokens);
                };
                break;
            default:
                printf("<< Unknown command! >>\n");
            };
    };

    return 0;
};
