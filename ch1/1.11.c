#include <stdio.h>

// counts number of lines, words and chars in input. Edge cases to test:
// multiple whitespace chars between adjacent words
// no words
// one word, no whitespace

#define IN 1
#define OUT 0

int main(void) {
    int c, nl, nw, nc, state;
    
    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        nc++;
        if (c == '\n') nl++;
        if (c == ' ' || c == '\n' || c == '\t') state = OUT;
        else if (state == OUT) {
            state = IN;
            nw++;
        }
    }

    printf("%d %d %d\n", nl, nw, nc);

    return 0;
}