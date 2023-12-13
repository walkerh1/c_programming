#include <stdio.h>

void squeeze(char s1[], const char s2[]);

int main(void) {
    char s1[] = { 'a', 'b', 'c', 'd', 'x', 'd', 'd', '\0' };
    char s2[] = { 'd', 'a', '\0' };

    printf("%s\n", s1);
    squeeze(s1, s2);
    printf("%s\n", s1);
}

void squeeze(char s1[], const char s2[]) {
    int i, j, k;
    for (i = 0; s2[i] != '\0'; i++) {
        for (j = k = 0; s1[j] != '\0'; j++) {
            if (s1[j] != s2[i]) {
                s1[k++] = s1[j];
            }
        }
        s1[k] = '\0';
    }
}
