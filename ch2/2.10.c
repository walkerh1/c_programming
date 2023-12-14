#include <stdio.h>

int lower(int c);

int main(void) {
    putchar(lower('a'));
    putchar(lower('A'));
    putchar(lower('c'));
    putchar(lower('C'));
    putchar(lower('z'));
    putchar(lower('Z'));
    putchar(lower('?'));
    putchar(lower('3'));

    return 0;
}

int lower(int c) {
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
