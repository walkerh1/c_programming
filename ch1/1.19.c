#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int maxline);
void reverse(char line[], int len);

int main(void) {
    int len; // current line length
    char line[MAXLINE]; // current input line

    while ((len = get_line(line, MAXLINE)) > 0) {
        reverse(line, len);
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

// reverse `s` 
void reverse(char s[], int len) {
    int lo = 0;
    int hi = len - 1;
    
    if (s[hi] == '\n') {
        hi--;
    }

    int tmp;
    while (lo < hi) {
        tmp = s[lo];
        s[lo] = s[hi];
        s[hi] = tmp;
        lo++;
        hi--;
    }
}