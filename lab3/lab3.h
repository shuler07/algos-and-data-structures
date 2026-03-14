#ifndef lab3_h
#define lab3_h

// get_string.c
char *get_string(int *expr_size);

// stack.c
typedef struct StackNode {
    char oper;
    int priority;
    struct StackNode *prev;
} StackNode;

typedef struct Stack {
    StackNode *top;
} Stack;

void stack_create(Stack *st);
void stack_push(Stack *st, char oper);
char stack_pop(Stack *st);

// tree.c
typedef struct TreeNode {
    char val;
    struct TreeNode *parent;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct Tree {
    TreeNode *root;
} Tree;

void tree_create(Tree *tr);
void tree_add(Tree *tr, char val);
void tree_print(TreeNode *node, int space);
void tree_remove_unary_minuses(Tree *tr, TreeNode *node);

// deykstra.c
char *get_postfix_expr(char *expr, int expr_size);

// convert.c
void postfix_expr_to_tree(char *expr, Tree *tr);
char *tree_to_expr(TreeNode *node, int expr_size);

#endif
