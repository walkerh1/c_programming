#include <stdio.h>

#define MAXCOLUMN 20    // max number of columns per line
#define TABWIDTH 8      // number of columns in a tab block
#define WORDWRAP 8      // if most recent blank is more than WORDWRAP from end of line, split word with '-'

// Fold lines longer than MAXCOLUMN chars long into the next line by
// putting the most recent word at the start of the next line. If the word is
// longer than TABWIDTH, than split the word with '-' instead.

int update_line(char line[], int pos);
int find_last_blank(const char line[], int n);
void print_up_to(char line[], int pos);

int main(void) {
    int c, pos;
    char line[MAXCOLUMN+1];

    pos = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            print_up_to(line, pos);
            putchar('\n');
            pos = 0;
            continue;
        }

        if (c == '\t') {
            // replace tabs with appropriate number of spaces
            int spaces = TABWIDTH - (pos % TABWIDTH);
            while (spaces > 0 && pos < MAXCOLUMN) {
                line[pos] = ' ';
                pos++;
                spaces--;
            }
            pos--;
        } else {
            line[pos] = (char) c;
        }

        if (pos == MAXCOLUMN) {
            pos = find_last_blank(line, pos);
            if (pos == -1) {
                pos = MAXCOLUMN-1;
                print_up_to(line, pos);
                putchar('-');
            } else {
                print_up_to(line, pos);
            }
            putchar('\n');
            pos = update_line(line, pos);
        }

        pos++;
    }

    print_up_to(line, pos);
}

// put wrapped portion of line at beginning of line buffer
int update_line(char line[], int pos) {
    int i, j;
    for (i = 0, j = pos; j <= MAXCOLUMN; i++, j++) {
        line[i] = line[j];
    }
    return i-1;
}

// find last blank in line buffer, or WORDWRAP limit if that is reached first
int find_last_blank(const char line[], int n) {
    while (n >= MAXCOLUMN - WORDWRAP && line[n] != ' ') {
        n--;
    }
    if (n < MAXCOLUMN - WORDWRAP) {
        return -1;
    }
    return n+1;
}

// print line up to but not including pos, trimming leading whitespace
void print_up_to(char line[], int pos) {
    int in_leading_whitespace = 1;
    for (int i = 0; i < pos; i++) {
        if (line[i] != ' ') {
           in_leading_whitespace = 0;
        }
        if (!in_leading_whitespace) {
            putchar(line[i]);
        }
    }
}