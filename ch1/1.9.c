#include <stdio.h>

int main(void) {
    int c;
    
    while ((c = getchar()) != EOF) {
        putchar(c);
        if (c == ' ') {
            while ((c = getchar()) != EOF && c == ' ');
            putchar(c);
        }
    }
}