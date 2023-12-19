#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100   // max size of value or operator
#define NUMBER '0'  // signal that a number was found
#define MAXVAL 100  // max depth of stack
#define BUFSIZE 100 // max size of buffer for ungetch

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

int sp = 0;         // next free stack position
double val[MAXVAL]; // value stack
char buf[BUFSIZE];  // buffer for ungetch
int bufp;           // next free position in buf

// reverse polish calculator
int main(void) {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                if ((op2 = pop()) != 0.0) {
                    push(pop() / op2);
                } else {
                    printf("error: zero division\n");
                }
                break;
            case '%':   // exercise 4.3
                if ((op2 = pop()) != 0.0) {
                    push((int)pop() % (int)op2);
                } else {
                    printf("error: zero division\n");
                }
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }

    return 0;
}

// push f onto value stack
void push(double f) {
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack is full, can't push %g\n", f);
    }
}

// pop and return top value from stack
double pop(void) {
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack is empty");
        return 0.0;
    }
}

// get next operator or numeric operand
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    // not a number
    if (!isdigit(c) && c != '.' && c != '-') {
        return c;
    }

    // decide if '-' being used as negation or minus operator
    i = 0;
    if (c == '-') {
        if (isdigit(c = getch())) {
            s[i] = '-';
            s[++i] = c;
        } else {
            ungetch(c);
            return '-';
        }
    }

    // collect integer part
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = getch()))
            ;
    }

    // collect fractional part
    if (c == '.') {
        while (isdigit(s[++i] = c = getch()))
            ;
    }

    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }

    return NUMBER;
}

// get a possibly pushed back character
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

// push character back onto input
void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}