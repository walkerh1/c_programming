#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main(void) {
  char s1[] = "endian";
  char s2[] = "end";
  squeeze(s1, s2);
  printf("squeeze(\"endian\", \"end\") gives %s\n", s1);
  return 0;
}

void squeeze(char s1[], char s2[]) {
  int i, j, k;
  for (k = 0; s2[k] != '\0'; k++) {
    for (i = j = 0; s1[i] != '\0'; i++) {
      if (s1[i] != s2[k]) {
        s1[j++] = s1[i];
      }
    }
    s1[j] = '\0';
  }
}