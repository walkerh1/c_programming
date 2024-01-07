#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int to_lower = 1; // default is to convert to lowercase

int main(int argc, char *argv[]) {
    int c;

    if (argc == 2) {
        if (strcmp(argv[1], "-u") == 0) {
            to_lower = 0;
        } else if (strcmp(argv[1], "-l") != 0) {
            printf("usage: caseconvert -[u|l]\n");
            exit(1);
        }
    }

    while ((c = getchar()) != EOF) {
        putchar(to_lower ? tolower(c) : toupper(c));
    }

    return 0;
}