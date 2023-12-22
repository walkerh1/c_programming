#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTACK 1000

// TODO(hugo): prints garbage for invalid expressions, improve error reporting
int main(int argc, char *argv[]) {
    int stack[MAXSTACK];
    int op1, op2, sp = 0;
    char *arg;

    while (--argc) {
        arg = *++argv;
        if (isdigit(*arg)) {
            stack[sp++] = atoi(arg);
        } else if (strcmp(arg, "+") == 0) {
            op1 = stack[--sp];
            op2 = stack[--sp];
            stack[sp++] = op1 + op2;
        } else if (strcmp(arg, "-") == 0) {
            op1 = stack[--sp];
            op2 = stack[--sp];
            stack[sp++] = op2 - op1;
        } else if (strcmp(arg, "*") == 0) {
            op1 = stack[--sp];
            op2 = stack[--sp];
            stack[sp++] = op1 * op2;
        } else if (strcmp(arg, "/") == 0) {
            op1 = stack[--sp];
            op2 = stack[--sp];
            if (op1 == 0) {
                printf("error: cannot divide by 0\n");
                return 1;
            } else {
                stack[sp++] = op2 / op1;
            }
        }
    }

    printf("%d\n", stack[--sp]);

    return 0;
}