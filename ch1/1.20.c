#include <stdio.h>

// Should convert tabs into spaces, but not simply by substituting in
// say 8 spaces for every \t char encountered. E.g. if the line is already
// 3 columns into the current tab block when it hits a \t, then it should
// replace that \t with 8 - 3 = 5 spaces, not 8.

// To test: a.out < 1.20.in.txt > 1.20.out.txt

#define TABSIZE 8 // assume a tab is 8 columns wide
#define MAXLINE 1000

int get_line_detab(char line[], int max_line, int tab_size);

int main(void) {
    int len;
    char line[MAXLINE];

    while ((len = get_line_detab(line, MAXLINE, TABSIZE)) > 0) {
        if (len > 0) {
            printf("%s", line);
        }
    }

    return 0;
}

// get line and replace any tabs with appropriate number of spaces
int get_line_detab(char s[], int lim, int tab_size) {
    int c, i;

    i = 0;
    while (i < lim-1 && (c=getchar())!=EOF && c!='\n') {
        if (c == '\t') {
            int spaces = tab_size - (i % tab_size);
            for (int j = 0; j < spaces; j++) {
               s[i] = ' '; 
               i++;
            }
        } else {
            s[i] = c;
            i++;
        }
    }

    if (c == '\n') {
        s[i] = c;
        i++;
    }

    s[i] = '\0';
    return i;
}