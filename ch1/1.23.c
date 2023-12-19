#include <stdio.h>

// Removes all block and inline C comments.

int main(void) {
    int c, prev;

    while ((c = getchar()) != EOF) {
        if (c == '"') {
            // print everything inside double quotes
            putchar(c);
            while ((c = getchar()) != EOF && c != '"') {
                putchar(c);
            }
            putchar(c);
        } else if (c == '\'') {
            // print everything inside single quotes
            putchar(c);
            while((c = getchar()) != EOF && c != '\'') {
                putchar(c);
            }
            putchar(c);
        } else if (c == '/') {
            prev = c;
            c = getchar();
            if (c == '*') {
                // found '/*' - skip over everything until '*/' is reached
                while ((c = getchar()) != EOF) {
                    if (c == '*') {
                        if ((c = getchar()) == '/') {
                            break;
                        }
                    }
                }
            } else if (c == '/') {
                // found '//' - skip over the rest of line
                while ((c = getchar()) != EOF && c != '\n');
                if (c == '\n') {
                    putchar(c);
                }
            } else {
                // found '/' in a non-comment context
                putchar(prev);
                putchar(c);
            }
        } else {
            putchar(c);
        }
    }
}