#include <stdio.h>
#include <string.h>

int strend(char *s, char *t);

int main(void) {
    char s[] = "hello world";
    char t[] = "hello c";
    char u[] = "world";

    printf("strend(%s, %s) == %d\n", s, u, strend(s, u));
    printf("strend(%s, %s) == %d\n", t, u, strend(t, u));

    return 0;
}

int strend(char *s, char *t) {
    int dist = strlen(s) - strlen(t);

    if (dist < 0) {
        return 0;
    }

    s += dist;
    while (*s) {
        if (*s++ != *t++) {
            return 0;
        }
    }

    return 1;
}