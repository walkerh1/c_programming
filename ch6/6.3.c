#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100     // max length of word
#define MAXFREQ 100     // max frequency of any word
#define IGNORELEN sizeof(ignore_words) / sizeof(ignore_words[0])     // length of ignored words list

struct tnode {
    char *word;
    int lines[MAXFREQ];
    int lp;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
int binsearch(char *, char **, int);
struct tnode *talloc(void);
int getch(void);
void ungetch(int);

int ln = 1; // current line number

// list of ignored words in lexicographical order
char *ignore_words[] = {
    "a",
    "and",
    "in",
    "the"
};

// A cross-referencer that prints every word in a document, followed by a list of the line
// numbers on which they occur.
int main(void) {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (binsearch(word, ignore_words, IGNORELEN) < 0) {
            root = addtree(root, word);
        }
    }

    treeprint(root);
    return 0;
}

// add node with word at or below root or add line number if node already exists
struct tnode *addtree(struct tnode *root, char *word) {
    int cond;

    if (root == NULL) {
        root = talloc();
        root->word = strdup(word);
        root->lines[(root->lp)++] = ln;
        root->left = root->right = NULL;
    } else if ((cond = strcmp(word, root->word)) == 0) {
        root->lines[(root->lp)++] = ln;
    } else if (cond < 0) {
        root->left = addtree(root->left, word);
    } else {
        root->right = addtree(root->right, word);
    }

    return root;
}

// in order print of tree
void treeprint(struct tnode *root) {
    if (root == NULL) {
        return;
    }
    treeprint(root->left);
    printf("%s: ", root->word);
    int i;
    for (i = 0; i < root->lp - 1; i++) {
        printf("%d, ", root->lines[i]);
    }
    printf("%d\n", root->lines[i]);
    treeprint(root->right);
}

// Put next word in word buffer; return 0 if success, EOF otherwise.
// Definition of word is a sequence consisting of alphabetic letters,
// digits, '_', or '-', but must start and end with a letter or digit.
int getword(char *word, int lim) {
    int c;
    char *w = word;

    // skip until alphanumeric character reached (or EOF)
    while ((c = getch()) != EOF && !isalnum(c))
        ;

    if (c == EOF) {
        *w = '\0';
        return c;
    } else {
        *w++ = c;
    }

    // get rest of characters in word
    for ( ; --lim > 0; w++) {
        if (!isalnum(*w = getch()) && *w != '_' && *w != '-') {
            ungetch(*w);
            break;
        }
    }

    // Remove trailing '_' or '-'
    while (w > word && (*(w-1) == '_' || *(w-1) == '-')) {
        w--;
    }

    *w = '\0';
    return 0;
}

// find word in ignore_words array
int binsearch(char *word, char *ignore[], int n) {
    int cond;
    int lo, mid, hi;

    lo = 0;
    hi = n;
    while (lo < hi) {
        mid = (lo + hi) / 2;
        if ((cond = strcmp(word, ignore[mid])) < 0) {
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
    char c = (bufp > 0) ? buf[--bufp] : getchar();
    if (c == '\n') {
        ln++;
    }
    return c;
}

// push char back onto input stream
void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        if (c == '\n') {
            ln--;
        }
        buf[bufp++] = c;
    }
}
