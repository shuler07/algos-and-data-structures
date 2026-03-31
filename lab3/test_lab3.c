#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "lab3.h"


void test_expr_1() {
    char expr[16] = "a*(-b)*3";
    List tokens;
    list_create(&tokens);
    printf("\nTesting 1 expression - %s\n", expr);

    char *postfix_expr = get_postfix_expr(expr, 16, &tokens);
    char answer[7] = "ab~*3*";
    assert(strcmp(postfix_expr, answer) == 0);
    assert(strcmp(tokens.first->token, "a") == 0);
    assert(strcmp(tokens.first->next->token, "b") == 0);
    printf("[ + ] Postfix expression, tokens\n");

    Tree tree_expr;
    tree_create(&tree_expr);
    postfix_expr_to_tree(&tokens, &tree_expr);
    assert(strcmp(tree_expr.root->val, "*") == 0);
    assert(strcmp(tree_expr.root->right->val, "3") == 0);
    assert(strcmp(tree_expr.root->left->val, "*") == 0);
    assert(strcmp(tree_expr.root->left->right->val, "~") == 0);
    assert(strcmp(tree_expr.root->left->right->right->val, "b") == 0);
    assert(strcmp(tree_expr.root->left->left->val, "a") == 0);
    printf("[ + ] Tree expression\n");

    tree_remove_unary_minuses(tree_expr.root, &tree_expr);
    assert(strcmp(tree_expr.root->val, "~") == 0);
    printf("[ + ] Tree procedure\n");

    char *final_expr = tree_to_expr(tree_expr.root, 16);
    assert(strcmp(final_expr, "-(a*b*3)") == 0);
    printf("[ + ] Expression from tree\n");

    printf("Tests passed for expression 1\n");
};
 
void test_expr_2() {
    char expr[16] = "(-a*b)+5";
    List tokens;
    list_create(&tokens);
    printf("\nTesting 2 expression - %s\n", expr);

    char *postfix_expr = get_postfix_expr(expr, 16, &tokens);
    char answer[7] = "a~b*5+";
    assert(strcmp(postfix_expr, answer) == 0);
    assert(strcmp(tokens.first->token, "a") == 0);
    assert(strcmp(tokens.first->next->token, "~") == 0);
    printf("[ + ] Postfix expression, tokens\n");

    Tree tree_expr;
    tree_create(&tree_expr);
    postfix_expr_to_tree(&tokens, &tree_expr);
    assert(strcmp(tree_expr.root->val, "+") == 0);
    assert(strcmp(tree_expr.root->right->val, "5") == 0);
    assert(strcmp(tree_expr.root->left->val, "*") == 0);
    assert(strcmp(tree_expr.root->left->right->val, "b") == 0);
    assert(strcmp(tree_expr.root->left->left->val, "~") == 0);
    assert(strcmp(tree_expr.root->left->left->right->val, "a") == 0);
    printf("[ + ] Tree expression\n");

    tree_remove_unary_minuses(tree_expr.root, &tree_expr);
    assert(strcmp(tree_expr.root->val, "~") != 0);
    assert(strcmp(tree_expr.root->left->val, "~") == 0);
    printf("[ + ] Tree procedure\n");

    char *final_expr = tree_to_expr(tree_expr.root, 16);
    assert(strcmp(final_expr, "(-(a*b))+5") == 0);
    printf("[ + ] Expression from tree\n");

    printf("Tests passed for expression 2\n");
};

void test_expr_3() {
    char expr[16] = "-a*3";
    List tokens;
    list_create(&tokens);
    printf("\nTesting 3 expression - %s\n", expr);

    char *postfix_expr = get_postfix_expr(expr, 16, &tokens);
    char answer[5] = "a~3*";
    assert(strcmp(postfix_expr, answer) == 0);
    assert(strcmp(tokens.first->token, "a") == 0);
    assert(strcmp(tokens.first->next->token, "~") == 0);
    printf("[ + ] Postfix expression, tokens\n");

    Tree tree_expr;
    tree_create(&tree_expr);
    postfix_expr_to_tree(&tokens, &tree_expr);
    assert(strcmp(tree_expr.root->val, "*") == 0);
    assert(strcmp(tree_expr.root->right->val, "3") == 0);
    assert(strcmp(tree_expr.root->left->val, "~") == 0);
    assert(strcmp(tree_expr.root->left->right->val, "a") == 0);
    printf("[ + ] Tree expression\n");

    tree_remove_unary_minuses(tree_expr.root, &tree_expr);
    assert(strcmp(tree_expr.root->val, "~") == 0);
    printf("[ + ] Tree procedure\n");

    char *final_expr = tree_to_expr(tree_expr.root, 16);
    assert(strcmp(final_expr, "-(a*3)") == 0);
    printf("[ + ] Expression from tree\n");

    printf("Tests passed for expression 3\n");
};

int main() {
    test_expr_1();
    test_expr_2();
    test_expr_3();  
};
