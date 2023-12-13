#include <stdio.h>
#include <stdbool.h>

#define MAXSTACK 100

bool input_is_balanced();

int main(void) {
    if (input_is_balanced()) {
        printf("input is balanced\n");
    } else {
        printf("input is not balanced\n");
    }
}

bool input_is_balanced() {
    int c, sp;
    char stack[MAXSTACK];

    sp = 0;
    while ((c = getchar()) != EOF) {
        if (c == '[' || c == '(' || c == '{') {
            stack[sp] = (char) c;
            sp++;
        } else if (c == ']') {
            if (sp > 0 && stack[sp-1] == '[') {
                sp--;
            } else {
                return false;
            }
        } else if (c == ')') {
            if (sp > 0 && stack[sp-1] == '(') {
                sp--;
            } else {
                return false;
            }
        } else if (c == '}') {
            if (sp > 0 && stack[sp-1] == '{') {
                sp--;
            } else {
                return false;
            }
        } else if (c == '"') {
            while ((c = getchar()) != EOF && c != '"');
            if (c != '"') {
                return false;
            }
        } else if (c == '\'') {
            while ((c = getchar()) != EOF && c != '\'');
            if (c != '\'') {
                return false;
            }
        } else if (c == '/') {
            c = getchar();
            if (c == '/') {
                while ((c = getchar()) != EOF && c != '\n');
            } else if (c == '*') {
                int closed = 0;
                while ((c = getchar()) != EOF) {
                    if (c == '*') {
                        if ((c = getchar()) == '/') {
                            closed = 1;
                            break;
                        }
                    }
                }
                if (!closed) {
                    return false;
                }
            }
        }
    }

    return sp == 0;
}