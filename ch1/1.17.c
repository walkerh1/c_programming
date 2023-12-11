#include <stdio.h>

#define MAXLINE 1000
#define LINELEN 80

int get_line(char line[], int maxline);

int main(void) {
    int len; // current line length
    char line[MAXLINE]; // current input line

    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > LINELEN) {
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