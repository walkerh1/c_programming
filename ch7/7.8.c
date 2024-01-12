#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100
#define PAGELEN 20

int main(int argc, char *argv[]) {
    FILE *fp;
    void fileprint(FILE *, char *);
    char *prog = argv[0];

    if (argc == 1) {
        fprintf(stderr, "%s: must provide at least one file as argument.\n", prog);
        exit(1);
    }

    while (--argc > 0) {
        if ((fp = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "%s: cannot open %s\n", prog, *argv);
            exit(1);
        } else {
            fileprint(fp, *argv);
            fclose(fp);
        }
    }

    return 0;
}

void fileprint(FILE *fp, char *fname) {
    int lineno = 0, pageno = 1;
    char line[MAXLINE];

    while (fgets(line, MAXLINE, fp) != NULL) {
        if (++lineno == 1) {
            printf("\n\n[%s] page %d\n\n", fname, pageno);
            lineno += 3;
        }
        fputs(line, stdout);
        if (lineno+1 == PAGELEN) {
            pageno++;
            lineno = 0;
        }
    }

    int rem = PAGELEN - lineno;
    while (rem-- > 0) {
        putchar('\n');
    }
}