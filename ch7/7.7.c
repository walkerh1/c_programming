#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

void match(char *, FILE *);

int except = 0, number = 0, found = 0;

// find: print lines that match pattern
int main(int argc, char *argv[]) {
    FILE *fp;
    char line[MAXLINE], *pattern, *prog;
    int c;

    prog = *argv;   // program name

    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
        }
    }

    if (argc == 0) {
        printf("usage: find -x -n pattern <file1> <file2> ...\n");
    } else {
        pattern = *argv;
        if (argc == 1) {    // if no more args, read from stdin
            match(pattern, stdin);
        }
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "%s: cannot open %s\n", prog, *argv);
                exit(1);
            } else {
                match(pattern, fp);
                fclose(fp);
            }
        }
    }

    return found;
}

void match(char *pattern, FILE *fp) {
    long lineno = 0;
    char line[MAXLINE];

    while (fgets(line, MAXLINE, fp) != NULL) {
        lineno++;
        if ((strstr(line, pattern) != NULL) != except) {
            if (number) {
                printf("%ld: ", lineno);
            }
            printf("%s", line);
            found++;
        }
    }
}