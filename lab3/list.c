#include <stdio.h>
#include <stdlib.h>
#include "lab3.h"


void list_create(List *lst) {
    lst->first = NULL;
    lst->last = NULL;
};

void list_clear(List *lst) {
    ListNode *cur = lst->first;
    while (cur) {
        ListNode *garbage = cur;
        cur = cur->next;
        free(garbage);
    };
    list_create(lst);
};

void list_push_begin(List *lst, char *token) {
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) {
        printf("<< Memory allocation error! >>\n");
        return;
    };
    node->token = token;
    if (!lst->first) {
        node->prev = NULL;
        node->next = NULL;
        lst->first = node;
        lst->last = node;
        return;
    };
    node->prev = NULL;
    node->next = lst->first;
    lst->first = node;
    ListNode *cur = lst->last;
    while (cur->prev) cur = cur->prev;
    cur->prev = node;
};

void list_push_end(List *lst, char *token) {
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) {
        printf("<< Memory allocation error! >>\n");
        return;
    };
    node->token = token;
    if (!lst->last) {
        node->prev = NULL;
        node->next = NULL;
        lst->first = node;
        lst->last = node;
        return;
    };
    node->prev = lst->last;
    node->next = NULL;
    lst->last = node;
    ListNode *cur = lst->first;
    while (cur->next) cur = cur->next;
    cur->next = node;
};

char *list_pop_begin(List *lst) {
    if (!lst->first) return NULL;
    ListNode *first_node = lst->first;
    char *value = first_node->token;
    lst->first = first_node->next;
    if (!lst->first) lst->last = NULL;
    free(first_node);
    return value;
};

char *list_pop_end(List *lst) {
    if (!lst->last) return NULL;
    ListNode *last_node = lst->last;
    char *value = last_node->token;
    lst->last = last_node->prev;
    if (!lst->last) lst->first = NULL;
    free(last_node);
    return value;
};

void list_print(List *lst) {
    printf(" => Postfix expression tokens:\n[");
    ListNode *current = lst->first;
    while (current) {
        if (current->next) printf("%s, ", current->token);
        else printf("%s", current->token);
        current = current->next;
    };
    printf("]\n");
};
