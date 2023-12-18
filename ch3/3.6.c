#include <stdio.h>
#include <string.h>

#define MAXLEN 10 // max number of decimal digits in signed/unsigned int is 9, +1 for possible '-' sign

void itoa(int n, char s[], int width);
void reverse(char s[]);
int abs(int n);

int main(void) {
    char num[MAXLEN];
    itoa(1000, num, 10);
    printf("itoa(%d) = %s\n", 1000, num);
    return 0;
}

// converts int into ascii with minimum width, padding with space on the left if needed.
void itoa(int n, char s[], int width) {
    int i, sign;

    if ((sign = n) < 0) {
        n = -n;
    }

    i = 0;
    do {
        s[i++] = (char)(abs(n % 10) + '0');
    } while ((n /= 10) != 0);

    if (sign < 0) {
        s[i++] = '-';
    }

    while (i < width) {
       s[i++] = ' ';
    }

    s[i] = '\0';

    reverse(s);
}

void reverse(char s[]) {
    int i, j;
    char tmp;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}

// precondition: 0 <= n <= 9
// This is because in the only place this function is called, it is
// passed an argument of the form n == x % 10.
int abs(int n) {
    return n < 0 ? -n : n;
}
