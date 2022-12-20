#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <HashTable.h>

#undef DEBUG // already defined in HashTable. TODO move debug_msg out of it
#define DEBUG 1

// O(n*n) and uses no additional space/data structures
bool is_unique_slow(char* s) {
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (i == j) {
                continue;
            }
            if (s[i] == s[j]) {
                return false;
            }
        }
    }
    return true;
}

int compare(const void* a, const void* b) {
    return strcmp(a, b);
}

// O(N log n) e.g. with quicksort
bool is_unique_sorted(char* s) {

    char* sorted = strdup(s);
    int len = strlen(sorted);
    qsort(sorted, len, 1, compare);
    
    for (int i = 0; i < len - 1; i++) {
        if (sorted[i] == sorted[i+1]) {
            return false;
        }
    }
    return true;
}

// O(N) with hash table
bool is_unique_ht(char* s) {
    HashTable* ht = ht_create();
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        if (ht_contains(ht, s[i]))
        {
            return false;
        }
        ht_add(ht, s[i], 0);
    }

    ht_free(ht);
    return true;
}

int main(int argv, char** argc) {

    char* unique = "qwer1234";
    char* not_unique = "qwer123q";

    assert(is_unique_ht(unique));
    assert(!is_unique_ht(not_unique));

    assert(is_unique_sorted(unique));
    assert(!is_unique_sorted(not_unique));

    assert(is_unique_slow(unique));
    assert(!is_unique_slow(not_unique));

    return 0;
}
