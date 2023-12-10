#include <stdio.h>

int main(void) {
    int c, bc, tc, nc;
    bc = tc = nc = 0;
    
    while ((c = getchar()) != EOF) {
        if (c == '\n') nc++;
        else if (c == ' ') bc++;
        else if (c == '\t') tc++;
    }

    printf("blank count: %d\n", bc);
    printf("tab count: %d\n", tc);
    printf("newline count: %d\n", nc);
}