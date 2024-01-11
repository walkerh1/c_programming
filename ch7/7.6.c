#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100

int main(int argc, char *argv[]) {
    FILE *fp1, *fp2;
    int lineno;
    char line1[MAXLINE], line2[MAXLINE];
    char *prog = argv[0];   // program name

    // check correct command line args provided
    if (argc != 3) {
        fprintf(stderr, "usage: %s <file1> <file2>\n", prog);
        exit(1);
    }

    // open file 1
    if ((fp1 = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s: cannot open %s\n", prog, argv[1]);
        exit(1);
    }

    // open file 2
    if ((fp2 = fopen(argv[2], "r")) == NULL) {
        fprintf(stderr, "%s: cannot open %s\n", prog, argv[2]);
        exit(1);
    }

    // compare files
    lineno = 1;
    while (fgets(line1, MAXLINE, fp1) != NULL && fgets(line2, MAXLINE, fp2) != NULL) {
        if (strncmp(line1, line2, MAXLINE) != 0) {
            printf("line %d\n", lineno);
            printf("%s: %s", argv[1], line1);
            printf("%s: %s", argv[2], line2);
        }
        lineno++;
    }

    // check whether one file ends earlier than the other
    if (feof(fp1) == 0 && feof(fp2) != 0) {
        // file2 ended before file1
        printf("end of second file at line %d: %s", --lineno, line2);
    } else if (feof(fp1) != 0 && feof(fp2) == 0) {
        // file1 ended before file2
        printf("end of first file at line %d: %s", --lineno, line1);
    }

    // close files
    fclose(fp1);
    fclose(fp2);

    return 0;
}