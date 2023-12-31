#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define PREFIXLEN 6
#define NKEYS (sizeof keytab / sizeof(keytab[0]))

struct key {
    char *word;
    int count;
};

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
int getword(char *, int);
int binsearch(char *, struct key *, int);
struct tnode *talloc(void);
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

// variable name frequency count
int main(void) {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) || word[0] == '_') {
            if (binsearch(word, keytab, NKEYS) < 0) { // check word is NOT a keyword
                root = addtree(root, word, PREFIXLEN);
            }
        }
    }

    treeprint(root);
    return 0;
}

// add or increment a node with word at or below root
struct tnode *addtree(struct tnode *root, char *word, int len) {
    int cond;

    if (root == NULL) {
        root = talloc();
        root->word = strndup(word, len);
        root->count = 1;
        root->left = root->right = NULL;
    } else if ((cond = strncmp(word, root->word, len)) == 0) {
        root->count++;
    } else if (cond < 0) {
        root->left = addtree(root->left, word, len);
    } else {
        root->right = addtree(root->right, word, len);
    }

    return root;
}

// in order print of tree
void treeprint(struct tnode *root) {
    if (root == NULL) {
        return;
    }
    treeprint(root->left);
    printf("%4d %s\n", root->count, root->word);
    treeprint(root->right);
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

struct tnode *talloc(void) {
    return (struct tnode *)malloc(sizeof(struct tnode));
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
