#include <stdio.h>

// replace each string of one or more blanks in the input with
// a single blank in the output

int main(void) {
    int c;
    
    while ((c = getchar()) != EOF) {
        putchar(c);
        if (c == ' ') {
            while ((c = getchar()) != EOF && c == ' ');
            putchar(c);
        }
    }

    return 0;
}