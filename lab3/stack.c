#include <stdio.h>
#include <stdlib.h>
#include "lab3.h"


void stack_create(Stack *st) {
    st->top = NULL;
};

void stack_push(Stack *st, char oper) {
    StackNode *node = (StackNode*)malloc(sizeof(StackNode));
    if (!node) {
        printf("<< Memory allocation error! >>\n");
        return;
    };

    node->oper = oper;
    if (!st->top) {
        node->prev = NULL;
        st->top = node;
        return;
    };
    node->prev = st->top;
    st->top = node;
};

char stack_pop(Stack *st) {
    StackNode *top = st->top;
    if (!top) return '\0';
    char res = top->oper;
    st->top = top->prev;
    free(top);
    return res;
};
