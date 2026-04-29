#include <stdlib.h>
#include <stdio.h>
#include "lab5.h"


void listCreate(List *lst) {
    lst->root = NULL;
};

void listAdd(List *lst, int a, int b, int len) {
    Node *node = (Node*)malloc(sizeof(Node));
    if (!node) {
        printf("<< Memory allocation error >>\n");
        return;
    };
    node->a = a;
    node->b = b;
    node->len = len;

    if (!lst->root) {
        node->prev = node->next = NULL;
        lst->root = node;
        return;
    };

    Node *cur = lst->root;
    while (len > cur->len && cur->next) cur = cur->next;

    if (len > cur->len) {
        node->prev = cur;
        node->next = cur->next;
        if (cur->next) cur->next->prev = node;
        cur->next = node;
        return;
    }
    node->prev = cur->prev;
    node->next = cur;
    if (!cur->prev) lst->root = node;
    else cur->prev->next = node;
    cur->prev = node;
};
