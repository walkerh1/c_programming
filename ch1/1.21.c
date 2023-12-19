#include <stdio.h>

// Should convert all spaces leading up to a tab break into a tab,
// unless it is only one space away from the tab break, in which
// case leave it as a space.

// To test: a.out < 1.21.in.txt > 1.21.out.txt

#define TABSIZE 8 // assume a tab is 8 columns wide
#define MAXLINE 1000

int get_line_entab(char line[], int max_line, int tab_size);

int main(void) {
    int len;
    char line[MAXLINE];

    while ((len = get_line_entab(line, MAXLINE, TABSIZE)) > 0) {
        if (len > 0) {
            printf("%s", line);
        }
    }

    return 0;
}

// replace adjacent blocks of spaces with a tab
int get_line_entab(char s[], int lim, int tab_size) {
    int c, i, j, num_spaces;
    i = num_spaces = 0;
    j = 1;
    while (i < lim-1 && (c=getchar())!=EOF && c!='\n') {
        if (c == ' ') {
            num_spaces++;
            if (num_spaces > 1 && (j % tab_size == 0)) {
                s[i] = '\t';
                num_spaces = 0;
                i++;
            }
        } else {
            while (num_spaces) {
                s[i] = ' ';
                num_spaces--;
                i++;
            }
            s[i] = c;
            i++;
        }
        j++;
    }

    if (c == '\n') {
        s[i] = c;
        i++;
    }

    s[i] = '\0';
    return i;
}