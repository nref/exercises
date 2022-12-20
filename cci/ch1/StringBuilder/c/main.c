#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

typedef struct String_ {
    struct String_* next;
    char* data;
} String;

typedef struct {
    String* head;
    int len;
    String* tail;
} StringBuilder;

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

char* sb_to_string(StringBuilder* sb) {

    int total_len = 0;

    String* s = sb->head;

    while (s != NULL) {
        total_len += strlen(s->data);
        s = s->next;
    }

    char* ret = calloc(total_len, sizeof(char));

    s = sb->head;

    int i = 0;
    while (s != NULL) {
        int len = strlen(s->data);
        memcpy(&ret[i], s->data, len);
        s = s->next;
        i += len;
    }

    return ret;
}

void sb_append(StringBuilder *sb, char* data) {
    String* s_new = calloc(1, sizeof(String));
    s_new->data = strdup(data);
    s_new->next = NULL;

    if (sb->head == NULL) {
        sb->head = s_new;
    }
    if (sb->tail != NULL) {
      sb->tail->next = s_new;
    }

    sb->tail = s_new;
    sb->len++;
}

StringBuilder* sb_create() {
    StringBuilder* sb = calloc(1, sizeof(StringBuilder));
    sb->head = NULL;
    sb->tail = NULL;
    sb->len = 0;
    return sb;
}

void sb_destroy(StringBuilder* sb) {

    String* s = sb->head;

    while (s != NULL) {
        String* tmp = s;
        s = s->next;
        free(tmp ->data);
        free(tmp);
    }
    free(sb);
}

void sb_print(StringBuilder* sb) {
    debug_msg("StringBuilder (%d): \"%s\"", sb->len, sb_to_string(sb));
}

int main(int argv, char** argc) {
    StringBuilder* sb = sb_create();
    sb_append(sb, "test");
    sb_append(sb, "asdf");
    sb_append(sb, "1234");
    sb_print(sb);

    sb_destroy(sb);
    return 0;
}
