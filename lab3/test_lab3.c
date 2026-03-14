#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "lab3.h"


void test_expr_1() {
    char expr[16] = "a*(-b)*3";

    char *postfix_expr = get_postfix_expr(expr, 16);
    assert(strcmp(postfix_expr, "ab~*3*") == 0);

    Tree tree_expr;
    tree_create(&tree_expr);
    postfix_expr_to_tree(postfix_expr, &tree_expr);
    assert(tree_expr.root->val == '*');
    assert(tree_expr.root->right->val == '3');
    assert(tree_expr.root->left->val == '*');
    assert(tree_expr.root->left->right->val == '~');
    assert(tree_expr.root->left->right->right->val == 'b');
    assert(tree_expr.root->left->left->val == 'a');

    tree_remove_unary_minuses(&tree_expr, tree_expr.root);
    assert(tree_expr.root->val == '~');

    char *final_expr = tree_to_expr(tree_expr.root, 16);
    assert(strcmp(final_expr, "-(a*b*3)") == 0);

    printf("Tests passed for expression 1\n");
};
 
void test_expr_2() {
    char expr[16] = "-a*(-b)*5*d";

    char *postfix_expr = get_postfix_expr(expr, 16);
    assert(strcmp(postfix_expr, "a~b~*5*d*") == 0);

    Tree tree_expr;
    tree_create(&tree_expr);
    postfix_expr_to_tree(postfix_expr, &tree_expr);
    assert(tree_expr.root->val == '*');
    assert(tree_expr.root->right->val == 'd');
    assert(tree_expr.root->left->val == '*');
    assert(tree_expr.root->left->right->val == '5');
    assert(tree_expr.root->left->left->val == '*');
    assert(tree_expr.root->left->left->right->val == '~');
    assert(tree_expr.root->left->left->right->right->val == 'b');
    assert(tree_expr.root->left->left->left->val == '~');
    assert(tree_expr.root->left->left->left->right->val == 'a');

    tree_remove_unary_minuses(&tree_expr, tree_expr.root);
    assert(tree_expr.root->val != '~');

    char *final_expr = tree_to_expr(tree_expr.root, 16);
    assert(strcmp(final_expr, "a*b*5*d") == 0);

    printf("Tests passed for expression 2\n");
};

void test_expr_3() {
    char expr[16] = "-a*3";

    char *postfix_expr = get_postfix_expr(expr, 16);
    assert(strcmp(postfix_expr, "a~3*") == 0);

    Tree tree_expr;
    tree_create(&tree_expr);
    postfix_expr_to_tree(postfix_expr, &tree_expr);
    assert(tree_expr.root->val == '*');
    assert(tree_expr.root->right->val == '3');
    assert(tree_expr.root->left->val == '~');
    assert(tree_expr.root->left->right->val == 'a');

    tree_remove_unary_minuses(&tree_expr, tree_expr.root);
    assert(tree_expr.root->val == '~');

    char *final_expr = tree_to_expr(tree_expr.root, 16);
    assert(strcmp(final_expr, "-(a*3)") == 0);

    printf("Tests passed for expression 3\n");
};

int main() {
    test_expr_1();
    test_expr_2();
    test_expr_3();  
};
