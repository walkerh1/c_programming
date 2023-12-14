#include <stdio.h>

#define MAXLEN 100

void expand(const char s1[], char s2[]);

int main(void) {
    char s2[MAXLEN];
    char s1[] = "a-z\nA-Z\n0-9\na-b-c\n!-~";

    printf("before:\n%s\n", s1);
    expand(s1, s2);
    printf("\nafter:\n%s\n", s2);

    return 0;
}

void expand(const char s1[], char s2[]) {
    char c;
    int i, j;

    i = j = 0;
    while ((c = s1[i]) != '\0') {
        if (s1[i+1] == '-' && c < s1[i+2]) {
            while (c < s1[i+2]) {
                s2[j++] = c;
                c++;
            }
            i += 2;
        } else {
            s2[j++] = c;
            i++;
        }
    }
}