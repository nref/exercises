#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define BUCKET_COUNT 16

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

int get_byte(int number, int n) {
   return (number >> (n * 8)) & 0xFF;
}

int get_hash(int number) {
    // FNV-1a
    const unsigned long long big_prime = 14695981039346656037U;
    const unsigned long long little_prime = 1099511628211U;

    int hash = big_prime;
    const int nbytes = 4; // assume 32-bit integer
    for (int i = 0; i < nbytes; i++)
    {
        hash ^= little_prime;
        hash *= get_byte(number, i);
    }

    return hash;
}

HashTable* ht_create() {
   HashTable* ht = calloc(1, sizeof(HashTable));

   ht->buckets = calloc(BUCKET_COUNT, sizeof(Bucket));

   for (int i = 0; i < BUCKET_COUNT; i++)
   {
       ht->buckets[i].first = NULL;
   }

   return ht;
}

void bucket_add(Bucket* b, int value) {
    Entry* entry = b->first;

    // This is the first entry in the bucket
    if (entry == NULL) {
        entry = calloc(1, sizeof(Entry));
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
        Entry* tmp = entry->next;
        free(entry);
        entry = tmp;
    }
    free(b);
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
    free(ht);
}

void ht_print(HashTable* ht) {
    printf("HashTable:\r\n");

    for (int i = 0; i < BUCKET_COUNT; i++) {
        printf("Bucket %d: ", i);

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
    ht_print(ht);

    ht_remove(ht, key, value);

    bool contains = ht_contains(ht, key, value);

    ht_free(ht);
    return 0;
}
