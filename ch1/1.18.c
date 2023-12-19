#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int maxline);
int r_strip(char line[], int len);

// process input one line at a time
int main(void) {
    int len; // current line length
    char line[MAXLINE]; // current input line

    while ((len = get_line(line, MAXLINE)) > 0) {
        len = r_strip(line, len);
        if (len > 0) {
            printf("%s", line);
        }
    }

    return 0;
}

// read a line into `s`; return length
int get_line(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; i++) {
        s[i] = c;
    }

    if (c == '\n') {
        s[i] = c;
        i++;
    }
    
    s[i] = '\0';
    return i;
}

// strip trailing blanks and tabs; delete if whole line is whitespace; return length
int r_strip(char line[], int len) {
    int i = len - 1;
    if (line[i] == '\n') {
        i--;
    }

    while (i >= 0 && (line[i] == ' ' || line[i] == '\t')) {
        i--;
    }

    if (i == -1) {
        line[0] = '\0';
        return 0;
    }

    if (line[len-1] == '\n') {
        i++;
        line[i] = '\n';
    }

    i++;
    line[i] = '\0';

    return i;
}