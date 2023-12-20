#include <stdio.h>
#include <string.h>

void reverse(char s[], int lo, int hi);

int main(void) {
    char s[] = "hello, world";
    reverse(s, 0, strlen(s) - 1);
    printf("%s\n", s);

    return 0;
}

void reverse(char s[], int lo, int hi) {
    // base case
    if (lo > hi) {
        return;
    }

    // do work pre-recursion
    char tmp = s[lo];
    s[lo] = s[hi];
    s[hi] = tmp;

    // recurse
    reverse(s, lo+1, hi-1);
}