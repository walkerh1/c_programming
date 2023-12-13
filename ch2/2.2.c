#include <stdio.h>

#define MAXLINE 1000

int main(void) {
    int c, i;

    for (i = 0;; i++) {
        if (i >= MAXLINE - 1) {
            break;
        }

        if ((c = getchar()) == '\n') {
            break;
        }

        if (c == EOF) {
            break;
        }

        putchar(c);
    }

    putchar('\n');

    return 0;
}