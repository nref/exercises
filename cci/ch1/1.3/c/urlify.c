#include "string.h"
#include "stdio.h"

int main(int argc, char** argv) {
  char* input = "Mr John Smith      ";
  char* expected = "Mr%20John%20Smith";
  int len = 13; // verified below

  // count num spaces
  int nspaces = 0;
  for (int i = 0; i < len; i++) {
    if (input[i] == ' ') {
      nspaces++;
    }
  }

  // find real len
  int real_len = strlen(input) - 1;
  while (real_len > 0 && input[real_len] == ' ') {
    real_len--;
  }

  printf("%d\r\n", real_len);
  int j = strlen(input) - 1;
  for (int i = real_len; i >= 0; i--) {
    printf("%d %d\r\n", i, j);
    if (input[i] == ' ') {
      input[j] = '0';
      input[j-1] = '2';
      input[j-2] = '%';
      j -= 3;
    }
    else {
      input[j] = input[i];
      j -= 1;
    }
  }

  printf("\"%s\"", input);
  return 0;
}
