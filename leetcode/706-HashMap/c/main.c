/* 
 * Implements a basic hash table.
 * Handles collisions with linked lists.
 * The hash algo is FNV-1a.
 *
 * /
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define BUCKET_COUNT 16

// Entry_: temporary name so the struct can contain a pointer to the same type
typedef struct Entry_ { 
    int value;
    struct Entry_* next;
} Entry;

typedef struct {
    Entry* first;
    int length;
} Bucket;

typedef struct {
    Bucket* buckets;
} HashTable;

char get_byte(int number, int n) {
   return (number >> (n * 8)) & 0xFF;
}

int get_hash(int number) {
    // FNV-1a
    const unsigned long long big_prime = 14695981039346656037U;
    const unsigned long long little_prime = 1099511628211U;

    unsigned long long hash = big_prime;
    const int nbytes = 4; // assume 32-bit integer
    for (int i = 0; i < nbytes; i++)
    {
        hash ^= get_byte(number, i);
        hash *= little_prime;
    }

    return hash;
}

HashTable* ht_create() {
   HashTable* ht = calloc(1, sizeof(HashTable));

   ht->buckets = calloc(BUCKET_COUNT, sizeof(Bucket));

   for (int i = 0; i < BUCKET_COUNT; i++) {
       ht->buckets[i].first = NULL;
   }

   return ht;
}

void bucket_add(Bucket* b, int value) {
    Entry* entry = b->first;

    // This is the first entry in the bucket
    if (entry == NULL) {
        entry = calloc(1, sizeof(Entry));
        b->first = entry;
        entry->value = value;
        entry->next = NULL;
        b->length++;
        return;
    }

    // There is already an entry (hash collision occurred).
    // Traverse linked list, add entry to end
    while (entry->next != NULL) {
        entry = entry->next;
    }

    entry->next = calloc(1, sizeof(Entry));
    entry->next->value = value;
    entry->next->next = NULL;
    b->length++;
}

void bucket_remove(Bucket* b, int key, int value) {
    Entry* prev = NULL;
    Entry* entry = b->first;

    if (entry == NULL) {
        return; // unknown key. should we error?
    }

    while (entry != NULL) {
        if (entry->value == value) {
            if (prev != NULL) {
                prev->next = entry->next;
            }
            if (entry == b->first) {
                b->first = NULL;
            }
            free(entry);
            b->length--;
            break;
        }

        prev = entry;
        entry = entry->next;
    }
}

void bucket_free(Bucket* b) {
    Entry* entry = b->first;
    while (entry != NULL) {
        printf("Free entry (value=%d)\r\n", entry->value);
        Entry* tmp = entry->next;
        free(entry);
        entry = tmp;
    }
}

int get_bucket(int key) {
   return get_hash(key) % BUCKET_COUNT; 
}

void ht_add(HashTable* ht, int key, int value) {
   int bucket = get_bucket(key); 
   bucket_add(&ht->buckets[bucket], value);
}

void ht_remove(HashTable* ht, int key, int value) {
   int bucket = get_bucket(key); 
   bucket_remove(&ht->buckets[bucket], key, value);
}

bool ht_contains(HashTable* ht, int key, int value) {
   int bucket = get_bucket(key); 
   Entry* entry = ht->buckets[bucket].first;

   while (entry != NULL) {
       if (entry->value == value) {
           return true;
       }
       entry = entry->next;
   }
   return false; 
}

void ht_free(HashTable* ht) {
    for (int i = 0; i < BUCKET_COUNT; i++) {
        bucket_free(&ht->buckets[i]);
    }
    free(ht->buckets);
    free(ht);
}

void ht_print(HashTable* ht) {
    printf("HashTable:\r\n");

    for (int i = 0; i < BUCKET_COUNT; i++) {
        printf("  Bucket %d: ", i);

        Entry* entry = ht->buckets[i].first;
        while (entry != NULL) {
            printf("%d ", entry->value);
            entry = entry->next;
        }
        printf("\r\n");
    }
}

int main(int argv, char** argc) {
    int key = 1;
    int value = 5;
    HashTable* ht = ht_create();
    ht_add(ht, key, value);
    ht_add(ht, 1, 10);
    ht_add(ht, 1, 10);
    ht_add(ht, 1, 15);
    ht_add(ht, 2, 1);
    ht_print(ht);

    bool contains = ht_contains(ht, key, value);
    printf("Contains %d %d: %d\r\n", key, value, contains);

    ht_remove(ht, key, value);
    ht_free(ht);
    return 0;
}
