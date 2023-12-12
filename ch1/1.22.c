#include <stdio.h>

#define MAXCOLUMN 10
#define TABWIDTH 8
#define WORDWRAP 12

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

        line[pos] = c;
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

int update_line(char line[], int pos) {
    int i, j;
    for (i = 0, j = pos; j <= MAXCOLUMN; i++, j++) {
        line[i] = line[j];
    }
    return i-1;
}

int find_last_blank(const char line[], int n) {
    while (n >= 0 && line[n] != ' ') {
        n--;
    }
    return n==-1 ? -1 : n+1;
}

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