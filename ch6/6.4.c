#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXDISTINCT 200
#define IGNORELEN sizeof(ignore_words) / sizeof(ignore_words[0])

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void arrayprint(struct tnode **, int);
int getword(char *, int);
int binsearch(char *,char **, int);
int arrayify(struct tnode *, struct tnode **);
void quick_sort(struct tnode *nodes[], int left, int right);
struct tnode *talloc(void);
int getch(void);
void ungetch(int);

// list of ignored words in lexicographical order
char *ignore_words[] = {
        "a",
        "and",
        "in",
        "the"
};

// word frequency
int main(void) {
    struct tnode *root;
    char word[MAXWORD];
    struct tnode *nodes[MAXDISTINCT];

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (binsearch(word, ignore_words, IGNORELEN) < 0) {
            root = addtree(root, word);
        }
    }

    int len = arrayify(root, nodes);
    quick_sort(nodes, 0, len-1);
    arrayprint(nodes, len);

    return 0;
}

// add or increment a node with word at or below root
struct tnode *addtree(struct tnode *root, char *word) {
    int cond;

    if (root == NULL) {
        root = talloc();
        root->word = strdup(word);
        root->count = 1;
        root->left = root->right = NULL;
    } else if ((cond = strcmp(word, root->word)) == 0) {
        root->count++;
    } else if (cond < 0) {
        root->left = addtree(root->left, word);
    } else {
        root->right = addtree(root->right, word);
    }

    return root;
}

// in order print of tree
void arrayprint(struct tnode *nodes[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%4d %s\n", nodes[i]->count, nodes[i]->word);
    }
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

// represent tree as an array (order of array will be in-order tree traversal);
// returns length of resulting array
int arrayify(struct tnode *root, struct tnode *nodes[]) {
    static int i = 0;

    if (root == NULL) {
        return i;
    }

    arrayify(root->left, nodes);
    nodes[i++] = root;
    arrayify(root->right, nodes);

    return i;
}

// sort array by frequency
void quick_sort(struct tnode *nodes[], int left, int right) {
    int i, last;
    void swap(struct tnode *v[], int i, int j);

    if (left >= right) {
        return;
    }

    swap(nodes, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if (nodes[i]->count < nodes[left]->count) {
            swap(nodes, ++last, i);
        }
    }
    swap(nodes, left, last);
    quick_sort(nodes, left, last-1);
    quick_sort(nodes, last+1, right);
}

// swap v[i] and v[j]
void swap(struct tnode *v[], int i, int j) {
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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
