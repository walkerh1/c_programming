#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

int getint(int *);
int getch(void);
void ungetch(int);

int main(void) {
    int c, i;

    while ((c = getint(&i)) != EOF && c > 0) {
        printf("%d\n", i);
    }

    return 0;
}

// Get next integer from input and put it in *i.
// Returns positive value if next input is a number, 0 if next
// input is not a number, and EOF for end of file.
int getint(int *pn) {
    int c, sign;

    // skip whitespace
    while (isspace(c = getch()))
        ;

    // return 0 if not a number
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    // get sign of number
    sign = (c == '-') ? -1 : 1;

    // check for optional '+' or '-'
    if (c == '+' || c == '-') {
        c = getch();
        // return 0 if no digit immediately after '+' or '-'
        if (!isdigit(c)) {
            ungetch(c);
            return 0;
        }
    }

    // convert ascii into int value and put in *pn
    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }

    // add sign to int
    *pn *= sign;

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