/* 
 * Implements a basic hash table.
 * Handles collisions with linked lists.
 * The hash algo is FNV-1a.
 *
 */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

#define BUCKET_COUNT 16
#define DEBUG 0

// Entry_: temporary name so the struct can contain a pointer to the same type
typedef struct Entry_ { 
    int key;
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

char get_byte(char* data, int n) {
    return data[n];
}

int debug_msg(const char* fmt, ...) {
    if (!DEBUG) return 0;
    va_list args;
    va_start(args, fmt);
    int ret = vprintf(fmt, args);
    va_end(args);
    return ret;
}

unsigned long long get_hash_raw(char* data, int nbytes) {
    // FNV-1a https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1a_hash
    const unsigned long long big_prime = 14695981039346656037U;
    const unsigned long long little_prime = 1099511628211U;

    unsigned long long hash = big_prime;
    for (int i = 0; i < nbytes; i++)
    {
        hash ^= get_byte(data, i);
        hash *= little_prime;
    }

    return hash;
}

unsigned long long get_hash(int number) {
    const int nbytes = 4; // assume 32-bit integer
    return get_hash_raw((char*)&number, nbytes);
}

HashTable* ht_create() {
   HashTable* ht = calloc(1, sizeof(HashTable));

   ht->buckets = calloc(BUCKET_COUNT, sizeof(Bucket));

   for (int i = 0; i < BUCKET_COUNT; i++) {
       ht->buckets[i].first = NULL;
   }

   return ht;
}

Entry* entry_create(int key, int value) {
    Entry* entry = calloc(1, sizeof(Entry));
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
    return entry;
}

void bucket_add(Bucket* b, int key, int value) {
    Entry* entry = b->first;

    // This is the first entry in the bucket
    if (entry == NULL) {
        debug_msg("bucket_add: adding first entry %d->%d\n", key, value);
        entry = entry_create(key, value);
        b->first = entry;
        b->length++;
        return;
    }

    // There is already an entry (hash collision occurred).
    // Traverse linked list. If key exists, update the entry.
    Entry* prev = NULL;
    while (entry != NULL) {
        if (entry->key == key)
        {
            debug_msg("bucket_add: updating entry %d->%d\n", key, value);
            entry->value = value;
            return;
        }
        prev = entry;
        entry = entry->next;
    }

    // Key does not exist, add it
    debug_msg("bucket_add: adding nonfirst entry %d->%d\n", key, value);
    prev->next = entry_create(key, value);
    b->length++;
}

void bucket_remove(Bucket* b, int key) {
    Entry* prev = NULL;
    Entry* entry = b->first;

    if (entry == NULL) {
        return; // unknown key. should we error?
    }

    // Traverse list, remove first key match
    while (entry != NULL) {
        if (entry->key == key) {
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
        debug_msg("free entry (key,value)=(%d,%d)\r\n", entry->key, entry->value);
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
   debug_msg("ht_add: got bucket %d for key %d\r\n", bucket, key);
   bucket_add(&ht->buckets[bucket], key, value);
}

bool ht_try_get(HashTable* ht, int key, int* value) {
   int bucket = get_bucket(key); 
   Entry* entry = ht->buckets[bucket].first;

   while (entry != NULL) {
       if (entry->key == key) {
           *value = entry->value;
           return true;
       }
       entry = entry->next;
   }
   return false; 
}

void ht_remove(HashTable* ht, int key) {
   int bucket = get_bucket(key); 
   bucket_remove(&ht->buckets[bucket], key);
}

bool ht_contains(HashTable* ht, int key) {
   int bucket = get_bucket(key); 
   Entry* entry = ht->buckets[bucket].first;

   while (entry != NULL) {
       if (entry->key == key) {
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
        Entry* entry = ht->buckets[i].first;
        while (entry != NULL) {
            printf("  %d->%d\r\n", entry->key, entry->value);
            entry = entry->next;
        }
    }
}

void ht_print_buckets(HashTable* ht) {
    printf("  Buckets:\r\n");

    for (int i = 0; i < BUCKET_COUNT; i++) {
        printf("    Bucket %d: ", i);

        Entry* entry = ht->buckets[i].first;
        while (entry != NULL) {
            printf("%d->%d ", entry->key, entry->value);
            entry = entry->next;
        }
        printf("\r\n");
    }
}

void stress_test(HashTable* ht) {
    for (int i = 0; i < 1024; i++) {
        ht_add(ht, i, i*i);
    }
}

void test_add(HashTable* ht) {
    ht_add(ht, 1, 5);

    int result;
    bool got = ht_try_get(ht, 1, &result);
    
    assert(got);
    assert(result == 5);

    ht_remove(ht, 1);
}

void test_contains(HashTable *ht) {
    ht_add(ht, 1, 5);
    bool contains = ht_contains(ht, 1);
    assert(contains);
    ht_remove(ht, 1);
}

void test_remove(HashTable *ht) {
    ht_add(ht, 1, 5);
    ht_remove(ht, 1);
    bool contains = ht_contains(ht, 1);
    assert(!contains);
}

void test_add_same_key(HashTable *ht) {
    ht_add(ht, 1, 5);
    ht_add(ht, 1, 10);
    ht_add(ht, 1, 10);
    ht_add(ht, 1, 15);
    ht_add(ht, 2, 1);

    int result1;
    int result2;
    bool got1 = ht_try_get(ht, 1, &result1);
    bool got2 = ht_try_get(ht, 2, &result2);

    assert(got1);
    assert(got2);

    assert(result1 == 15);
    assert(result2 == 1);
}

