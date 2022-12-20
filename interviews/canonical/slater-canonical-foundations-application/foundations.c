// Doug Slater
// Code Exercise for Canonical Foundations Team
// 2022-12-12
// I ran this with: gcc -Wall foundations.c -o foundations && ./foundations

#include <stdio.h> // Just for printf

typedef enum { false, true } bool;

// Calculate the length of a string 
int strlen(char* s)
{
  int i = 0;
  while (s[i++] != '\0') {}
  return --i; // decrement excludes \0
}

// Convert the given char to a single-digit integer
// Return -1 if it is not an integer
int char_to_int(char s)
{
  switch (s)
  {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    default: return -1;
  }
}

// Convert a string to an integer. 
// Any non-integer characters are skipped, e.g. "12dog3" => 123
// Exception: A minus sign in the first index negates the integer
int atoi(char* s)
{
  int sum = 0; // Contains the unnegated result
  int place = 1; // The value of the current decimal place e.g. 10^n e.g. 1 => 0's, 2 => 10's, 3 => 100's, 4 => 1000's

  int len = strlen(s); // Eat our own dogfood
  int i = len - 1; // Index into s
  int negate = s[0] == '-' ? -1 : 1;

  // Iterate from the end of the string to the beginning
  // We do this because the end contains the least-significant digit e.g. 0's,
  // while the beginning contains the most-significatn digit e.g. 1000's
  while (i >= 0)
  {
    int n = char_to_int(s[i]);
    if (n == -1)
    {
      i--;
      continue; // Skip non-integer character
    }

    sum += place * n;
    place *= 10;
    i--;
  }

  return negate * sum;
}

bool test_strlen(char* s, int expected)
{
  int result = strlen(s);
  bool ok = result == expected;
  char* pass = ok ? "PASS " : "FAIL";

  printf("%s: strlen(\"%s\") returned %d, expected %d\n", pass, s, result, expected);
  return ok;
}

bool test_atoi(char* s, int expected)
{
  int result = atoi(s);
  bool ok = result == expected;
  char* pass = ok ? "PASS " : "FAIL";

  printf("%s: atoi(\"%s\") returned %d, expected %d\n", pass, s, result, expected);
  return ok;
}

int main() 
{
  bool ok1 = test_strlen("", 0);
  ok1 &= test_strlen("a", 1);
  ok1 &= test_strlen("1234", 4);
  ok1 &= test_strlen("1234_1234_1234_1234_1234_1234_1234_1234_1234_1234_", 5*10);

  printf("\n");
  bool ok2= test_atoi("0", 0);
  ok2 &= test_atoi("1", 1);
  ok2 &= test_atoi("12", 12);
  ok2 &= test_atoi("123", 123);
  ok2 &= test_atoi("12dog3", 123);
  ok2 &= test_atoi("2147483647", 2147483647);
  ok2 &= test_atoi("-1", -1);
  ok2 &= test_atoi("-2147483648", -2147483648);

  return ok1 && ok2 ? 0 : -1;
}
