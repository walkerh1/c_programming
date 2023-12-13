#include <stdio.h>

#define MAXLEN 100

int htoi(char s[]);

int main(void) {
   char s[MAXLEN];
   int c;
   int i = 0;
   while (i < MAXLEN-1 && (c = getchar()) != EOF && c != '\n') {
      s[i] = c;
      i++;
   }
   s[i] = '\0';
   printf("%s (base16) = %d (base10)\n", s, htoi(s));
   return 0;
}

// PRE: s is a hexidecimal number
int htoi(char s[]) {
   int start = 0;
   int result = 0;
   int hex;

   if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
      start += 2;
   }

   for (int i = start; s[i] != '\0'; i++) {
      if (s[i] >= 'A' && s[i] <= 'F') {
         hex = s[i] - 'A' + 10;
      } else if (s[i] >= 'a' && s[i] <= 'f') {
         hex = s[i] - 'a' + 10;
      } else if (s[i] >= '0' && s[i] <= '9') {
         hex = s[i] - '0';
      }
      result = hex + 16 * result;
   }

   return result;
}

