#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// Only added sin, cos, tan for exercise 4.5, adding other math.h functions is trivial.

#define NUMBER '0'      // signal to indicate a number token
#define PEEK '1'        // signal to execute peek command: write 'pk' in calculator
#define DUP '2'         // signal to execute duplicate command: write 'dup' in calculator
#define SWAP '3'        // signal to execute swap command: write 'swp' in calculator
#define CLEAR '4'       // signal to execute clear command: write 'clr' in calculator
#define SIN '5'         // signal to execute sine command: write 'sin' in calculator
#define COS '6'         // signal to execute cosine command: write 'cos' in calculator
#define TAN '7'         // signal to execute tangent command: write 'tan' in calculator
#define ILLEGAL (-1)    // signal to indicate an illegal token

#define MAXSTACK 100    // max depth of calculator stack
#define MAXLINE 100     // max size of line buffer
#define MAXNUM 100      // max size of num buffer

int next_token();
int readline(void);
void readnum(void);
void push(double);
double pop(void);

int sp = 0;             // next free stack position
double val[MAXSTACK];   // value stack
int lp = 0;             // next position in current line
char line[MAXLINE+1];   // buffer for current line
char num[MAXNUM+1];     // buffer for current number token

// reverse polish calculator
int main(void) {
    int token;
    double op1, op2;

    while (readline() != 0) {
        while ((token = next_token()) != '\0') {
            switch (token) {
                case NUMBER:
                    push(atof(num));
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
                        push(val[sp - 1]);
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
                case SIN:
                    if (sp > 0) {
                        push(sin(pop()));
                    } else {
                        printf("error: stack is empty, nothing to pass sin\n");
                    }
                    break;
                case COS:
                    if (sp > 0) {
                        push(cos(pop()));
                    } else {
                        printf("error: stack is empty, nothing to pass cos\n");
                    }
                    break;
                case TAN:
                    if (sp > 0) {
                        push(tan(pop()));
                    } else {
                        printf("error: stack is empty, nothing to pass tan\n");
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
                        push((int) pop() % (int) op2);
                    } else {
                        printf("error: zero division\n");
                    }
                    break;
                case '\n':
                    printf("\t%.8g\n", pop());
                    break;
                case ILLEGAL:
                    printf("error: illegal token found\n");
                    sp = 0;
                    break;
                default:
                    printf("error: unknown command\n");
                    sp = 0;
                    break;
            }
        }
    }
    return 0;
}

// get next token in line buffer
int next_token() {
    char c;

    // skip over leading whitespace
    while (line[lp] == ' ' || line[lp] == '\t') {
        lp++;
    }

    switch (line[lp]) {
        case 'p':
            lp++;
            if (line[lp] == 'k') {
                // pk (peek) command
                lp++;
                return PEEK;
            } else {
                return ILLEGAL;
            }
        case 'd':
            lp++;
            if (line[lp] == 'u' && line[lp + 1] == 'p') {
                // dup (duplicate) command
                lp += 2;
                return DUP;
            } else {
                return ILLEGAL;
            }
            break;
        case 's':
            lp++;
            if (line[lp] == 'w' && line[lp + 1] == 'p') {
                // swp (swap) command
                lp += 2;
                return SWAP;
            } else if (line[lp] == 'i' && line[lp + 1] == 'n') {
                // sin (sine) command
                lp += 2;
                return SIN;
            } else {
                return ILLEGAL;
            }
        case 'c':
            lp++;
            if (line[lp] == 'l' && line[lp + 1] == 'r') {
                // clr (clear) command
                lp += 2;
                return CLEAR;
            } else if (line[lp] == 'o' && line[lp + 1] == 's') {
                // cos (cosine) command
                lp += 2;
                return COS;
            } else {
                return ILLEGAL;
            }
        case 't':
            lp++;
            if (line[lp] == 'a' && line[lp + 1] == 'n') {
                // tan (tangent) command
                lp += 2;
                return TAN;
            } else {
                return ILLEGAL;
            }
        case '-':
            lp++;
            if ((c = line[lp]) == ' ' || c == '\t' || c == '\n' || c == '\0') {
                // binary minus operator
                return '-';
            } else if (isdigit(line[lp]) || line[lp] == '.') {
                // unary negation operator
                lp--;
                readnum();
                return NUMBER;
            } else {
                return ILLEGAL;
            }
        default:
            if (isdigit(line[lp]) || line[lp] == '.') {
                readnum();
                return NUMBER;
            } else {
                lp++;
                return line[lp - 1];
            }
    }
}

// read number into global numb buffer
void readnum(void) {
    int i = 0;

    // read potential negation symbol
    if (line[lp] == '-') {
        num[i] = '-';
        i++;
        lp++;
    }

    // read integral part of number
    while (isdigit(line[lp])) {
        num[i] = line[lp];
        i++;
        lp++;
    }

    // read fractional part of number if any
    if (line[lp] == '.') {
        num[i] = '.';
        i++;
        lp++;
        while (isdigit(line[lp])) {
            num[i] = line[lp];
            i++;
            lp++;
        }
    }

    num[i] = '\0';
}

// read next line into global line buffer, return length
int readline(void) {
    int c, i;
    i = 0;
    while (i < MAXLINE-1 && (c = getchar()) != '\n' && c != EOF) {
        line[i] = c;
        i++;
    }
    if (c == '\n') {
        line[i] = c;
        i++;
    }
    line[i] = '\0';
    lp = 0;
    return i;
}

// push f onto value stack
void push(double f) {
    if (sp < MAXSTACK) {
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
        printf("error: stack is empty\n");
        return 0.0;
    }
}
