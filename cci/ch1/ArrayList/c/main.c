#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

typedef struct {
    char* data;
    int len;
    int capacity;
} ArrayList;

int debug_msg(const char* fmt, ...) {
    if (!DEBUG)  {
        return 0;
    }

    va_list args;
    va_start(args, fmt);
    int ret = vprintf(fmt, args);
    va_end(args);

    return ret;
}

int al_grow(ArrayList* al) {
    const int GROW_FACTOR = 2;

    al->capacity *= GROW_FACTOR;
    char* data = calloc(al->capacity, sizeof(ArrayList));
    memcpy(data, al->data, al->len);

    free(al->data);
    al->data = data;

    debug_msg("al_grow(..): ok\r\n");
    return 0;
}

int al_insert_char(ArrayList* al, char c) {
    if (al->len == al->capacity) {
        if (al_grow(al) != 0) {
            return -1;
        }
    }

    al->data[al->len++] = c;
    return 0;
}

int al_insert(ArrayList* al, char* data, int len) {
    for (int i = 0; i < len; i++) {
        if (al_insert_char(al, data[i]) != 0) {
            return -1;
        }
    }
    return 0;
}

ArrayList* al_create(int capacity) {
    ArrayList* al = calloc(1, sizeof(ArrayList));
    al->capacity = capacity;
    al->data = calloc(al->capacity, sizeof(char));
    return al;
}

void al_destroy(ArrayList *al) {
    free(al->data);
    free(al);
}

void al_print(ArrayList* al) {
    debug_msg("ArrayList(%d/%d)[ ", al->len, al->capacity);
    for (int i = 0; i < al->len; i++) {
        debug_msg("%c ", al->data[i]);
    }
    for (int i = al->len; i < al->capacity; i++) {
        debug_msg(". ");
    }
    debug_msg("]\r\n");
}

int main(int argv, char** argc) {
    ArrayList* al = al_create(16);

    char str[1024];
    for (int i = 0; i < 17; i++) {
        al_print(al);
        sprintf(str, "%d", i);
        al_insert(al, str, strlen(str));
    }
    al_print(al);

    al_destroy(al);
    return 0;
}
