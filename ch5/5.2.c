#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

int getfloat(float *);
int getch(void);
void ungetch(int);

int main(void) {
    float f;
    int c;

    while ((c = getfloat(&f)) != EOF && c > 0) {
        printf("%f\n", f);
    }

    return 0;
}

// Get next float from input and put it in *pn.
// Returns positive int if next input is a float,
// 0 if not, and EOF if end of file.
int getfloat(float *pn) {
    int c;
    float exp, sign;

    // skip whitespace
    while (isspace(c = getch()))
        ;

    // return 0 if not a number
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }

    // get sign of number
    sign = (c == '-') ? -1 : 1;

    // check for optional '+' or '-'
    if (c == '+' || c == '-') {
        c = getch();
        // return 0 if no digit or '.' immediately after '+' or '-'
        if (!isdigit(c) && c != '.') {
            ungetch(c);
            return 0;
        }
    }

    // collect integral part of float
    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }

    // check for decimal point
    if (c == '.') {
        c = getch();
        // return success but put '.' back into stream if no digit after '.'
        if (!isdigit(c)) {
            ungetch(c);
            return c;
        }
    }

    // collect fractional part of float, keeping track of exponent
    for (exp = 1; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
        exp /= 10;
    }

    // adjust *pn for sign and exponent
    *pn = sign * exp * *pn;

    // put char back into byte stream unless EOF
    if (c != EOF) {
        ungetch(c);
    }

    return c;
}

//=============================================================================

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("error: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}
