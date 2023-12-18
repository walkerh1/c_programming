#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int get_line(char line[], int max);
int str_rindex(char s[], char t[]);

char pattern[] = "ould"; // pattern to search for

// find all lines matching pattern
int main(void) {
    char line[MAXLINE];
    int found = 0;
    while (get_line(line, MAXLINE) > 0) {
        if (str_rindex(line, pattern) >= 0) {
            printf("%s", line);
            found++;
        }
    }

    return 0;
}

// get line into s, return length
int get_line(char line[], int max) {
    int c, i;

    i = 0;
    while (--max > 0 && (c=getchar()) != EOF && c!='\n') {
        line[i++] = c;
    }
    if (c == '\n') {
        line[i++] = c;
    }
    line[i] = '\0';
    return i;
}

// return rightmost index of t in s, -1 if none
int str_rindex(char s[], char t[]) {
    int i, j, k;

    // start at rightmost len(t) window of s, and slide it left,
    // checking for matches on each shift
    for (i = strlen(s) - strlen(t); i >= 0; i--) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0') {
            return i;
        }
    }

    return -1;
}