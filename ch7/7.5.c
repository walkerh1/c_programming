#include <stdio.h>

#define MAXSTACK 100    // max depth of calculator stack
#define MAXSTR 100      // max length of scanned string

void push(double);
double pop(void);

int sp = 0;             // next free stack position
double val[MAXSTACK];   // value stack

// reverse polish calculator
int main(void) {
    char token;
    double op2;
    char string[MAXSTR];

    while (scanf("%s", string) != EOF) {
        if (sscanf(string, "%lf", &op2) == 1) {
            push(op2);
        } else if (sscanf(string, "%c", &token) == 1) {
            switch (token) {
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
                default:
                    printf("error: unknown command\n");
                    break;
            }
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
