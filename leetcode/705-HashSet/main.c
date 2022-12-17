#include <stdbool.h>
#include <stdlib.h>

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
    int size;
} HashSet;

HashSet* HashSet_Create() {
   HashSet* hs = calloc(1, sizeof(HashSet));

   hs->buckets = calloc(BUCKET_COUNT, sizeof(Bucket));
   hs->size = 0;

   for (int i = 0; i < BUCKET_COUNT; i++)
   {
       hs->buckets[i].first = NULL;
       hs->buckets[i].length = 0;
   }

   return hs;
}

void HashSet_Add(HashSet* obj, int key) {
  
}

void HashSet_Remove(HashSet* obj, int key) {
  
}

bool HashSet_Contains(HashSet* obj, int key) {
  
}

void HashSet_Free(HashSet* obj) {
    
}

int main(int argv, char** argc) {
    int key = 1;
    HashSet* obj = HashSet_Create();
    HashSet_Add(obj, key);

    HashSet_Remove(obj, key);

    bool param_3 = HashSet_Contains(obj, key);

    HashSet_Free(obj);
    return 0;
}
