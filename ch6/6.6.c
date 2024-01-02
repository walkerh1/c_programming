/*
 * block comment with #define %in %it
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define HASHSIZE 101
#define MAXWORD 100

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
int gettoken(char *word, int lim);

// hash table
static struct nlist *hashtable[HASHSIZE] = { NULL };

// flag for whether input stream is currently in a quote or comment
int in_quote_or_comment = 0;

// hash table entry
struct nlist {
    struct nlist *next; // next entry in chain
    char *name;         // defined name
    char *defn;         // replacement text
};

int main(void) {
    char c, word[MAXWORD], name[MAXWORD], defn[MAXWORD];
    struct nlist *entry;

    while ((c = gettoken(word, MAXWORD)) != EOF) {
        if ((entry = lookup(word)) != NULL && !in_quote_or_comment) {
            printf("%s", entry->defn);
        } else if (strcmp(word, "#define") == 0 && !in_quote_or_comment) {
            gettoken(word, MAXWORD); // consume ' '
            gettoken(name, MAXWORD);
            gettoken(word, MAXWORD); // consume ' '
            gettoken(defn, MAXWORD);
            printf("#define %s %s", name, defn);
            install(name, defn);
        } else if (isalpha(word[0]) || word[0] == '_' || word[0] == '#') {
            printf("%s", word);
        } else {
            putchar(c);
        }
    }

    return 0;
}

// get next word or character from input
int gettoken(char *word, int lim) {
    static int in_inline_comment = 0;
    int getch(void);
    void ungetch(int);
    int c, d;
    char *w = word;

    if ((c = getch()) != EOF) {
        *w++ = c;
    }

    if (isalnum(c) || c == '_' || c == '#') {   // word can start with letter, _, or #
        for ( ; --lim > 0; w++) {
            if (!isalnum(*w = getch()) && *w != '_') {  // non-first character can be letter, number, or _
                ungetch(*w);
                break;
            }
        }
    } else if (c == '"' || c == '\'') {
        in_quote_or_comment = !in_quote_or_comment;
    } else if (c == '/') {
        if ((d = getch()) == '/') {
            in_quote_or_comment = 1;
            in_inline_comment = 1;
        } else if (d == '*') {
            in_quote_or_comment = 1;
        }
        ungetch(d);
    } else if (c == '\n' && in_inline_comment) {
        in_inline_comment = 0;
        in_quote_or_comment = 0;
    } else if (c == '*') {
        if ((d = getch()) == '/') {
            in_quote_or_comment = !in_quote_or_comment;
        }
        ungetch(d);
    }

    *w = '\0';
    return c;
}

// form hash value for string
unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 + hashval;
    }
    return hashval % HASHSIZE;
}

// look for s in hash table
struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np = hashtable[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np;
        }
    }
    return NULL;
}

// put (name, defn) in hash table
struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL) {
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtable[hashval];
        hashtable[hashval] = np;
    } else {
        free((void *)np->defn);
    }

    if ((np->defn = strdup(defn)) == NULL) {
        return NULL;
    }

    return np;
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