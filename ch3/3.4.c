#include <stdio.h>
#include <string.h>

#define MAXLEN 10 // max number of decimal digits in signed/unsigned int is 9, +1 for possible '-' sign

void itoa(int n, char s[]);
void reverse(char s[]);
int abs(int n);

int main(void) {
    char num[MAXLEN];
    itoa(-2147483648, num);
    printf("itoa(%d) = %s\n", -2147483648, num);
    return 0;
}

// The reason this doesn't work for the largest negative number, e.g -2^31 for signed int,
// is because in twos complement the range of values for a signed integer type is [-X, X-1] for
// some X. E.g. the range for signed int is [-2^31, 2^31 - 1]. So if the naive function is passed
// n == -2^31, the first if condition passes and n is negated, to thereby make it positive. But
// trying to negate -2^31 won't result in 2^31, as might be expected, since 2^31 is out of range for
// the signed int type. What ends up happening in twos complement is -(-2^31) overflows back to itself.
// this means n will still equal -2^31 by the time it reaches the do-while loop. And since it's a
// do-while the body gets executed once without checking. This means '(' gets pushed onto the string
// buffer, as n % 10 evaluates to -8 and -8 + '0' evaluates to '(' in ascii. After this the loop
// condition fails, as n/10 is negative, and in the end the function returns with "-(" in the string buffer.
//
// To get around this, the while condition is changed to (n /= 10) != 0, allowing us to iterate over
// negative values of n, and the loop body is changed to use the absolute value of n % 10, which prevents
// us from ending up in non-digit regions of the ascii table.
void itoa(int n, char s[]) {
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
int abs(int n) {
    return n < 0 ? -n : n;
}
