#include <string.h>
#include <stdio.h>
#include <assert.h>

// print given string the given number of times
void printf_repeat(char* s, int n) {
  while (n-- > 0)
  {
    printf(s);
  }
}

int get_real_len(char* input) {
  int len = strlen(input);

  // find real len e.g. of "Mr John Smith" in "Mr John Smith    "
  int real_len = len - 1;
  while (real_len > 1 && input[real_len-1] == ' ') {
    real_len--;
  }

  return real_len;
}

int get_num_spaces(char* input, int real_len) {
  
  // count num spaces that we will substitute with "%20"
  int n_spaces = 0;
  for (int i = 0; i < real_len; i++) {
    if (input[i] == ' ') {
      n_spaces++;
    }
  }

  return n_spaces;
}

void replace_debug(int i, int j, char* input) {
    printf("\"%s\"\r\n", input);
    printf_repeat(" ", i+1);
    printf("|");
    printf_repeat("-", j-i-1);
    printf("^\r\n");
} 

// Replace in-place each occurrence of the given single character with the given string.
// If the given buffer is not long enough, do not make any changes.
void replace(char* input, char to_replace, char* replacement) {
  int replacement_len = strlen(replacement);

  int len = strlen(input);
  int real_len = get_real_len(input);
  int n_spaces = get_num_spaces(input, real_len);

  // verify we have enough buffer e.g. replacing two space chars ' ' each with "%20" => 2*(3 - 1) => 4
  const int original_len = 1;
  if (n_spaces*(replacement_len - original_len) + real_len > len)
  {
    printf("replace: Not enough buffer in string \"%s\". No changes made\r\n", input);
    return;
  }

  // Move index i right to left from end of real input string,
  // and move index j right to left from end of buffer.
  int i = real_len - 1;
  int j = len - 1;

  while (i >= 0 && i != j) {
    replace_debug(i, j, input);

    // If there's e.g. a space at i, write e.g. %20 at end of buffer pointer j, and walk j back 3.
    if (input[i] == to_replace) {
      int k = replacement_len - 1;
      while (k >= 0) {
        input[j--] = replacement[k--];
      }
    }
    // If there's a nonspace char at i, write it at j and walk j back 1.
    else {
      input[j--] = input[i];
    } 

    i--;
  }
}

// replace spaces with %20. the given buffer must be long enough to contain them else an assert fails.
void urlify(char* input) {
  replace(input, ' ', "%20");
}

int main(int argc, char** argv) {
  char input[] = "Mr John Smith    ";
  char expected[] = "Mr%20John%20Smith";

  urlify(input);
  printf("\"%s\"\r\n", input);
  assert(strcmp(expected, input) == 0);

  char input2[] = " a b c  "; // Deliberately not enough buffer
  char expected2[] = " a b c  ";
  urlify(input2);
  assert(strcmp(expected2, input2) == 0);
  return 0;
}
