#include <stdio.h>
#include <string.h>

#define MAXLEN 50

char *str_n_cpy(char *s, const char *ct, size_t n);
char *str_n_cat(char *s, const char *ct, size_t n);
int str_n_cmp(const char *cs, const char *ct, size_t n);

int main(void) {
    char s[MAXLEN] = "hello ";
    char t[] = "world, universe";
    char u[] = "hello world, how are you?";
    char v[MAXLEN];

    printf("u: \"%s\"\n", u);
    printf("v: \"%s\"\n", v);
    str_n_cpy(v, u, 11);
    printf("str_n_cpy(v, u, %d)\n", 11);
    printf("v: \"%s\"\n", v);

    printf("\ns: \"%s\"\n", s);
    printf("t: \"%s\"\n", t);
    str_n_cat(s, t, 5);
    printf("str_n_cat(s, t, %d)\n", 5);
    printf("s: \"%s\"\n", s);

    printf("\ns: %s\n", s);
    printf("v: %s\n", v);
    printf("str_n_cmp(s, v, %d) == %d\n", 11, str_n_cmp(s, v, 15));

    printf("\nstr_n_cmp(\"hell\", \"hello\", %d) == %d\n", 4, str_n_cmp("hell", "hello", 4));
    printf("str_n_cmp(\"hell\", \"hello\", %d) == %d\n", 5, str_n_cmp("hell", "hello", 5));
    printf("str_n_cmp(\"hello\", \"hell\", %d) == %d\n", 5, str_n_cmp("hello", "hell", 5));
    printf("str_n_cmp(\"hello\", \"hello\", %d) == %d\n", 5, str_n_cmp("hello", "hello", 5));
    printf("str_n_cmp(\"hello\", \"hello\", %d) == %d\n", 7, str_n_cmp("hello", "hello", 7));
    printf("str_n_cmp(\"hell\", \"help\", %d) == %d\n", 4, str_n_cmp("hell", "help", 4));

    return 0;
}

// copy at most n characters of ct into s; return s; pad with \0s if ct has fewer than n characters
char *str_n_cpy(char *s, const char *ct, size_t n) {
    char *dest = s;
    while (n--) {
        *dest++ = (*ct != '\0') ? *ct++ : '\0';
    }
    return s;
}

// concatenate at most n characters of ct to the end of s; return s
char *str_n_cat(char *s, const char *ct, size_t n) {
    char *dest = s + strlen(s);
    while ((*dest++ = *ct++) && --n)
        ;
    if (n) {
        // if here then fewer than n characters in ct; cap off with \0
        *dest = '\0';
    }
    return s;
}

// compare at most n characters of cs to ct; return -1 if cs<ct, 0 if cs==ct, 1 if cs>ct; lexicographical ordering
int str_n_cmp(const char *cs, const char *ct, size_t n) {
    char c;
    while ((c = *cs) != '\0' && (c == *ct) && --n) {
        cs++;
        ct++;
    }
    return *cs - *ct;
}