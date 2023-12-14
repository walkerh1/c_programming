#include <stdio.h>

int any(const char s1[], const char s2[]);

int main(void) {
    char s1[] = "abcdefg";
    char s2[] = "gb";

    printf("%d\n", any(s1, s2));

    return 0;
}

int any(const char s1[], const char s2[]) {
    int i, j;
    for (i = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                return i;
            }
        }
    }
    return -1;
}