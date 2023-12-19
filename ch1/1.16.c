#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

// print as much as possible of the longest line of input
int main(void) {
    int len; // current line length
    int max; // maximum length seen so far
    char line[MAXLINE]; // current input line
    char longest[MAXLINE]; // curren longest line

    max = 0;
    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
        printf("len: %d\n", len);
    }

    if (max > 0) {
        printf("%s", longest);
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

// copy `from` into `to`; assume `to` is big enough
void copy(char to[], char from[]) {
    int i = 0;
    while ((to[i] = from[i]) != '\0') {
        i++;
    }
}