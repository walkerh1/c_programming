#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100   // max size of value or operator
#define NUMBER '0'  // signal that a number was found
#define PEEK '1'    // signal to execute peek command: write 'pk' in calculator
#define DUP '2'     // signal to execute duplicate command: write 'du' in calculator
#define SWAP '3'    // signal to execute swap command: write 'sw' in calculator
#define CLEAR '4'   // signal to execute clear command: write 'cl' in calculator
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
    double op1, op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case PEEK:
                if (sp > 0) {
                    printf("\t%.8g\n", val[sp-1]);
                } else {
                    printf("error: stack is empty, nothing to peek at\n");
                }
                break;
            case DUP:
                if (sp > 0) {
                    push(val[sp-1]);
                } else {
                    printf("error: stack is empty, nothing to duplicate\n");
                }
                break;
            case SWAP:
                if (sp > 1) {
                    op1 = pop();
                    op2 = pop();
                    push(op1);
                    push(op2);
                } else {
                    printf("error: can't swap, stack needs at least two elements\n");
                }
                break;
            case CLEAR:
                sp = 0;
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
            case '%':
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

    // check for pk command
    if (c == 'p') {
        if ((c = getch()) == 'k') {
            return PEEK;
        } else {
            return 'p';
        }
    }

    // check for du command
    if (c == 'd') {
        if ((c = getch()) == 'u') {
            return DUP;
        } else {
            return 'd';
        }
    }

    // check for sw command
    if (c == 's') {
        if ((c = getch()) == 'w') {
            return SWAP;
        } else {
            return 's';
        }
    }

    // check for cl command
    if (c == 'c') {
        if ((c = getch()) == 'l') {
            return CLEAR;
        } else {
            return 'c';
        }
    }

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