#include <stdio.h>

// Return true if the char is an opening paren
bool opens(char c) {
    switch (c) {
        case '(':
        case '[':
        case '{':
          return true;
    }
    return false;
}

// Return true if the right paren closes the left paren
bool closes(char right, char left) {
    switch (right) {
        case ')': return left == '(';           
        case ']': return left == '[';
        case '}': return left == '{';
    }
    
    return false;
}

bool isValid(char* s) {
    int left = 0;
    int depth = 0;
    
    for (int i = 0;; i++) {      
        char c = s[i];
        printf("%c %d %d %d\n", c, i, left, depth);

        if (left < 0)
        {
            break;
        }
        
        if (c == '\0') 
        {
            break;
        }
        
        if (opens(c)) {
            left = i;
            depth++;
            continue;
        }
        
        if (closes(c, s[left])) {
            depth--;
            left--;
            continue;
        }
        
        return false;
    }
    
    printf("-----------\n");
    return left == 0 && depth == 0;
}
