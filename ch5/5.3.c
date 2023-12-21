#include <stdio.h>
#include <string.h>

#define MAXLEN 50

char *str_cat(char *s, const char *ct);

int main(void) {
    char s[MAXLEN] = "hello ";
    char t[] = "world";

    str_cat(s, t);

    printf("%s\n", s);

    return 0;
}

char *str_cat(char *s, const char *ct) {
    char *dest = s + strlen(s);
    while ((*dest++ = *ct++))
        ;
    return s;
}