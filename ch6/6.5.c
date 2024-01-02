#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void undef(char *);

// hash table
static struct nlist *hashtable[HASHSIZE] = { NULL };

// hash table entry
struct nlist {
    struct nlist *next; // next entry in chain
    char *name;         // defined name
    char *defn;         // replacement text
};

int main(void) {
    install("IN", "1");
    install("OUT", "0");

    printf("list[\"IN\"] = %s\n", lookup("IN")->defn);
    printf("list[\"OUT\"] = %s\n", lookup("OUT")->defn);

    printf("calling install(\"IN\", \"2\")...\n");
    install("IN", "2");
    printf("list[\"IN\"] = %s\n", lookup("IN")->defn);

    printf("calling undef(\"IN\")...\n");
    undef("IN");
    if (lookup("IN") == NULL) {
        printf("list[\"IN\"] = NULL\n");
    }

    return 0;
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
        printf("here\n");
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

// deletes the nlist element with name if in hash table;
// return 0 if success, -1 if not in table
void undef(char *name) {
    struct nlist *curr, *prev;
    unsigned h = hash(name);

    prev = NULL;
    curr = hashtable[h];
    while (curr != NULL) {
        if (strcmp(name, curr->name) == 0) {
            if (prev == NULL) {
                hashtable[h] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free((void *) curr->name);
            free((void *) curr->defn);
            free((void *) curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}
