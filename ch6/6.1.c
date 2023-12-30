#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(keytab[0]))

struct key {
    char *word;
    int count;
};

int getword(char *, int);
int binsearch(char *, struct key *, int);
int getch(void);
void ungetch(int);

struct key keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "do", 0,
    "double", 0,
    "else", 0,
    "enum", 0,
    "extern", 0,
    "float", 0,
    "for", 0,
    "goto", 0,
    "if", 0,
    "int", 0,
    "long", 0,
    "register", 0,
    "return", 0,
    "short", 0,
    "signed", 0,
    "sizeof", 0,
    "static", 0,
    "struct", 0,
    "switch", 0,
    "typedef", 0,
    "union", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};

// count C keywords
int main(void) {
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
                keytab[n].count++;
            }
        }
    }

    for (n = 0; n < NKEYS; n++) {
        if (keytab[n].count > 0) {
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
        }
    }

    return 0;
}

// get next word or character from input
int getword(char *word, int lim) {
    int c, d;
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c != EOF) {
        *w++ = c;
    }

    if (isalpha(c) || c == '_' || c == '#') {   // word can start with letter, _, or #
        for ( ; --lim > 0; w++) {
            if (!isalnum(*w = getch()) && *w != '_') {  // non-first character can be letter, number, or _
                ungetch(*w);
                break;
            }
        }
    } else if (c == '"' || c == '\'') { // skip over all characters inside quotes
        while ((d = getch()) != EOF && d != c)
            ;
    } else if (c == '/') {
        c = getch();
        if (c == '/') { // skip rest of line for inline comment
            while ((c = getch()) != EOF && c != '\n')
                ;
        } else if (c == '*') {    // skip rest of block comment
            while ((c = getch()) != EOF) {
                if (c == '*') {
                    if (getch() == '/') {
                        break;
                    }
                }
            }
        }
    }

    *w = '\0';
    return c;
}

// find word in tab array
int binsearch(char *word, struct key tab[], int n) {
    int cond;
    int lo, mid, hi;

    lo = 0;
    hi = n;
    while (lo < hi) {
        mid = (lo + hi) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0) {
            hi = mid;
        } else if (cond > 0) {
            lo = mid+1;
        } else {
            return mid;
        }
    }
    return -1;
}

// ======================= input utilities ======================= //

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

// get a possibly pushed back char
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

// push char back onto input stream
void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}
