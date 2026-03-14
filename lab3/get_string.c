#include <stdio.h>
#include <stdlib.h>
#include "lab3.h"


char *get_string(int *expr_size) {
    int buf_size = 16, ind = 0;
    char *buf = (char*)malloc(buf_size);
    if (!buf) {
        printf("Memory allocation error\n");
        return NULL;
    };
    char ch;
    scanf("%c", &ch);

    while (ch != '\n' && ch != '\r') {
        buf[ind++] = ch;
        if (ind + 1 == buf_size) {
            buf_size *= 2;
            char *new_buf = (char*)realloc(buf, buf_size);
            if (!new_buf) {
                printf("Memory allocation error\n");
                return NULL;
            };
            buf = new_buf;
        };
        scanf("%c", &ch);
    };

    buf[ind] = '\0';
    *expr_size = buf_size;
    return buf;
};
