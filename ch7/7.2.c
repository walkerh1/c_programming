#include <stdio.h>
#include <ctype.h>

#define MAXLEN 120
#define OCTLEN 3

int main(void) {
    int c, pos;

    pos = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || iscntrl(c)) {
            pos += OCTLEN;
            if (pos >= MAXLEN) {
                putchar('\n');
                pos = 0;
            }
            printf("%03o", c);
        } else {
            pos++;
            if (pos == MAXLEN) {
                putchar('\n');
                pos = 0;
            }
            putchar(c);
        }
    }

    return 0;
}