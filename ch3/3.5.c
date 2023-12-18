#include <stdio.h>
#include <string.h>

#define MAXLEN 10 // max number of decimal digits in signed/unsigned int is 9, +1 for possible '-' sign

void itob(int n, char s[], int base);
void reverse(char s[]);
int abs(int n);

int main(void) {
    char num[MAXLEN];
    itob(233, num, 2); printf("itob(%d, %d)  = %s\n", 233, 2, num);
    itob(233, num, 3); printf("itob(%d, %d)  = %s\n", 233, 3, num);
    itob(233, num, 4); printf("itob(%d, %d)  = %s\n", 233, 4, num);
    itob(233, num, 5); printf("itob(%d, %d)  = %s\n", 233, 5, num);
    itob(233, num, 6); printf("itob(%d, %d)  = %s\n", 233, 6, num);
    itob(233, num, 7); printf("itob(%d, %d)  = %s\n", 233, 7, num);
    itob(233, num, 8); printf("itob(%d, %d)  = %s\n", 233, 8, num);
    itob(233, num, 9); printf("itob(%d, %d)  = %s\n", 233, 9, num);
    itob(233, num, 10); printf("itob(%d, %d) = %s\n", 233, 10, num);
    itob(233, num, 11); printf("itob(%d, %d) = %s\n", 233, 11, num);
    itob(233, num, 12); printf("itob(%d, %d) = %s\n", 233, 12, num);
    itob(233, num, 13); printf("itob(%d, %d) = %s\n", 233, 13, num);
    itob(233, num, 14); printf("itob(%d, %d) = %s\n", 233, 14, num);
    itob(233, num, 15); printf("itob(%d, %d) = %s\n", 233, 15, num);
    itob(233, num, 16); printf("itob(%d, %d) = %s\n", 233, 16, num);

    return 0;
}

// precondition: 2 <= base <= 16
void itob(int n, char s[], int base) {
    int i, sign, rem;

    if ((sign = n) < 0) {
        n = -n;
    }

    i = 0;
    do {
        rem = abs(n % base);
        s[i++] = (char)(rem < 10 ? rem + '0' : rem + 'A');
    } while ((n /= base) != 0);

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

// precondition: 0 <= n <= 15
// This is because in the only place this function is called, it is
// passed an argument of the form n == x % base, and base is at most 16.
int abs(int n) {
    return n < 0 ? -n : n;
}
