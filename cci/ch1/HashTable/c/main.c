#include <HashTable.h>
#include <stdio.h>

int main(int argv, char** argc) {
    HashTable* ht = ht_create();

    test_add(ht);
    test_add_same_key(ht);
    test_contains(ht);
    test_remove(ht);

    ht_print(ht);
    ht_print_buckets(ht);

    printf("Contains key %d: %s\r\n", 1, ht_contains(ht, 1) ? "true" : "false");
    printf("Contains key %d: %s\r\n", 2, ht_contains(ht, 2) ? "true" : "false");

    ht_remove(ht, 1);
    ht_remove(ht, 2);

    stress_test(ht);
    ht_free(ht);
    return 0;
}
