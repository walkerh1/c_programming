#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int to_lower = 1; // default is to convert to lowercase

// Program that converts all text input into lower or upper case depending on the
// name of the executable.
int main(int argc, char *argv[]) {
    int c;

    if (strcmp(argv[0], "./upper") == 0) {
        to_lower = 0;
    } else if (strcmp(argv[0], "./lower") != 0) {
        printf("compile with name 'lower' or 'upper': gcc 7.1.c -o [lower|upper]\n");
        exit(1);
    }

    while ((c = getchar()) != EOF) {
        putchar(to_lower ? tolower(c) : toupper(c));
    }

    return 0;
}