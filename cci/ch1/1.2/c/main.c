#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../HashTable/c/HashTable.h"

int compare_strings(const void* s1, const void* s2) {
  return strcmp((char*)s1, (char*)s2);
}

// O (n log n). Sort each string in place and return true iff the sorted strings are equal.
bool is_permutation_sorted(char* s1, char* s2) {
  qsort(s1, strlen(s1), 1, compare_strings);
  qsort(s2, strlen(s2), 1, compare_strings);
  return compare_strings(s1, s2) == 0;
}

// works only if the char can be represented as an integer
void ht_insert_string(HashTable* ht, char* s) {

  int len = strlen(s);
  for (int i = 0; i < len; i++) {

    int c = (int)s[i];
    int* count = NULL;

    if (ht_try_get(ht, c, count)) {
      (*count)++;
    }
    else {
      ht_add(ht, c, 1);
    }
  }
}

// O(n). Put the chars of each string in a hash table. 
// Verify that each string's chars are in the other string's table.
bool is_permutation_hashtable(char* s1, char* s2) {
  HashTable* ht1 = ht_create();
  HashTable* ht2 = ht_create();

  ht_insert_string(ht1, s1);
  ht_insert_string(ht2, s2);

  for (int i = 0; i < strlen(s1); i++) {
    if (!ht_contains(ht2, (int)s1[i])) {
      return false;
    }
  }

  for (int i = 0; i < strlen(s2); i++) {
    if (!ht_contains(ht1, (int)s2[i])) {
      return false;
    }
  }

  return true;
}

int main(int argc, char** argv) {

  char s1[] = "racecar";
  char s2[] = "acerarc";
  char s3[] = "zcerarc";
  
  assert(is_permutation_sorted(s1, s2));
  assert(is_permutation_sorted(s1, s2));

  assert(!is_permutation_hashtable(s1, s3));
  assert(!is_permutation_hashtable(s1, s3));
  return 0;
}
