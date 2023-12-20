#include <stdio.h>

#define MAXBUFFER 15

void itoa(int n, char s[]);

int main(void) {
    char s[MAXBUFFER];
    itoa(-12345, s);
    printf("%s\n", s);

    return 0;
}

void itoa(int n, char s[]) {
    static int i = 0;

    if (n < 0) {
        s[i++] = '-';
        n = -n;
    }

    // base case
    if (n == 0) {
        return;
    }

    // recursive case
    itoa(n/10, s);

    // update s post-induction to get the right order
    s[i] = n % 10 + '0';
    s[++i] = '\0';
}