#include <stdio.h>

int any(char s1[], char s2[]);

int main(void) {
  printf("any(\"endian\", \"end\") gives %d\n", any("endian", "end"));
  printf("any(\"monster\", \"stone\") gives %d\n", any("monster", "stone"));
  printf("any(\"brain\", \"a\") gives %d\n", any("brain", "a"));
  printf("any(\"brain\", \"goo\") gives %d\n", any("brain", "goo"));
  return 0;
}

int any(char s1[], char s2[]) {
  int i, j;
  int earliest = -1;
  for (i = 0; s2[i] != '\0'; i++) {
    for (j = 0; s1[j] != '\0'; j++) {
      if (s1[j] == s2[i]) {
        if (j < earliest || earliest == -1) {
          earliest = j;
        }
      }
    }
  }
  return earliest;
}