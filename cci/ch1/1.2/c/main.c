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
    int count = 0;

    if (ht_try_get(ht, c, &count)) {
      ht_add(ht, c, count + 1);
    }
    else {
      ht_add(ht, c, 1);
    }
  }
}

// O(n). Put the chars of each string in a hash table. 
// Verify that the hash tables are equal (have the same keys and values)
bool is_permutation_hashtable(char* s1, char* s2) {
  if (strlen(s1) != strlen(s2)) {
    return false;
  }

  HashTable* ht1 = ht_create();
  HashTable* ht2 = ht_create();

  ht_insert_string(ht1, s1);
  ht_insert_string(ht2, s2);

  for (int i = 0; i < strlen(s1); i++) {
    int count1 = 0;
    int count2 = 0;

    // bail if a char in s2 is not in s1
    if (!ht_try_get(ht1, (int)s2[i], &count1)) {
      return false;
    }

    // bail if a char in s1 is not in s2
    if (!ht_try_get(ht2, (int)s1[i], &count2)) {
      return false;
    }

    // bail if a char occurs more in s1 or s2
    if (count1 != count2) {
      return false;
    }
  }

  return true;
}

int main(int argc, char** argv) {

  char s1[] = "racecar";
  char s2[] = "acerarc";
  char s3[] = "zcerarc";
  char s4[] = "cerarc";
  
  assert(is_permutation_sorted(s1, s2));
  assert(!is_permutation_sorted(s1, s3));
  assert(!is_permutation_sorted(s1, s4));
  assert(!is_permutation_sorted(s4, s1));

  assert(is_permutation_hashtable(s1, s2));
  assert(!is_permutation_hashtable(s1, s3));
  assert(!is_permutation_hashtable(s4, s1));
  return 0;
}
