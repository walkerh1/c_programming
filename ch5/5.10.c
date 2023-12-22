#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXSTACK 100    // max depth of calculator stack

int next_token(char *s);
void push(double);
double pop(void);

int sp = 0;             // next free stack position
double val[MAXSTACK];   // value stack

// Adapted from the reverse polish calculator from exercises 4.3 - 4.10.
// NOTE: must wrap "*" in quotes in shell
int main(int argc, char *argv[]) {
    double op2;
    char *arg;

    while (--argc) {
        arg = *++argv;
        if (isdigit(arg[0])) {
            push(atof(arg));
        } else if (strcmp(arg, "+") == 0) {
            push(pop() + pop());
        } else if (strcmp(arg, "*") == 0) {
            push(pop() * pop());
        } else if (strcmp(arg, "-") == 0) {
            op2 = pop();
            push(pop() - op2);
        } else if (strcmp(arg, "/") == 0) {
            if ((op2 = pop()) != 0.0) {
                push(pop() / op2);
            } else {
                printf("error: zero division\n");
                return 1;
            }
        } else if (strcmp(arg, "%") == 0) {
            if ((op2 = pop()) != 0.0) {
                push((int) pop() % (int) op2);
            } else {
                printf("error: zero division\n");
                return 1;
            }
        } else {
            printf("error: unknown command\n");
            return 1;
        }
    }

    printf("%f\n", pop());

    return 0;
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
