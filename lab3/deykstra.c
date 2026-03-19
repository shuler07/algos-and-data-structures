#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lab3.h"


bool is_oper(char ch) {
    return (strchr("()+-*/^", ch) != NULL);
};

int oper_priority(char oper) {
    switch (oper) {
        case '(': return 0;
        case ')': return 1;
        case '+':
        case '-': return 2;
        case '*':
        case '/': return 3;
        case '^': return 4;
        case '~':
        case '$': return 5;
        default: return -1;
    };
};

char *get_postfix_expr(char *expr, int expr_size, List *tokens) {
    int ind = 0;
    char *res = (char*)malloc(expr_size);
    res[0] = '\0';

    Stack opers;
    stack_create(&opers);

    char num[16];
    int num_ind = 0;

    int i = -1;
    while (expr[++i] != '\0') {
        char ch = expr[i];
        if (!is_oper(ch)) {
            if (num_ind != 0 && '0' <= ch <= '9'); // raise error
            if ('0' <= ch <= '9') {
                num[num_ind++] = ch;
                continue;
            };
        };

        if (num_ind != 0) {
            num[num_ind] = '\0';
            list_push_end(tokens, strdup(num));
            for (int j = 0; j < num_ind; j++) res[ind++] = num[j];
            num[0] = '\0';
            num_ind = 0;
        };

        // Унарный минус
        if (ch == '-' && (i == 0 || expr[i-1] == '(' || (is_oper(expr[i-1]) && expr[i-1] != ')'))) ch = '~';
        // Унарный плюс
        if (ch == '+' && (i == 0 || expr[i-1] == '(' || (is_oper(expr[i-1]) && expr[i-1] != ')'))) ch = '$';

        if (ch == '(') stack_push(&opers, ch);
        else if (ch == ')') {
            while ((ch = stack_pop(&opers)) != '(') {
                char str[2] = { ch, '\0' };
                list_push_end(tokens, strdup(str));
                res[ind++] = ch;
            };
        } else {
            while (opers.top && oper_priority(opers.top->oper) >= oper_priority(ch)) {
                char popped = stack_pop(&opers);
                char str[2] = { popped, '\0' };
                list_push_end(tokens, strdup(str));
                res[ind++] = popped;
            };
            stack_push(&opers, ch);
        };
    };

    if (num_ind != 0) {
        num[num_ind] = '\0';
        list_push_end(tokens, strdup(num));
        for (int j = 0; j < num_ind; j++) res[ind++] = num[j];
        num[0] = '\0';
        num_ind = 0;
    };
    while (opers.top) {
        char popped = stack_pop(&opers);
        char str[2] = { popped, '\0' };
        list_push_end(tokens, strdup(str));
        res[ind++] = popped;
    };
    res[ind] = '\0';

    return res;
};
