#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lab3.h"


bool is_oper(char ch) {
    return (strchr("()+-*/", ch) != NULL);
};

int priority(char oper) {
    switch (oper) {
        case '(': return 0;
        case ')': return 1;
        case '+':
        case '-': return 2;
        case '*':
        case '/': return 3;
        case '~': return 4;
    };
    return -1;
};

char *get_postfix_expr(char *expr, int expr_size) {
    int ind = 0;
    char *res = (char*)malloc(expr_size);

    Stack opers;
    stack_create(&opers);

    int i = -1;
    while (expr[++i] != '\0') {
        char ch = expr[i];
        if (!is_oper(ch)) {
            res[ind++] = ch;
            continue;
        };

        // Унарный минус
        if (ch == '-' && (i == 0 || expr[i-1] == '(' || is_oper(expr[i-1]))) ch = '~';

        if (ch == '(') stack_push(&opers, ch);
        else if (ch == ')') while ((ch = stack_pop(&opers)) != '(') res[ind++] = ch;
        else {
            while (opers.top && opers.top->priority >= priority(ch)) res[ind++] = stack_pop(&opers);
            stack_push(&opers, ch);
        };
    };
    while (opers.top) res[ind++] = stack_pop(&opers);
    res[ind] = '\0';

    return res;
};
