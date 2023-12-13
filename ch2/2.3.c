#include <stdio.h>

int htoi(const char s[]);

int main(void) {
    char n1[] = { '0', 'x', 'c', '3', '\0' };
    char n2[] = { '0', 'x', '1', '4', '\0'};
    char n3[] = { 'c', '3', 'e', '9', '0', '\0' };
    char n4[] = { 'c', '3', 'E', '9', '0', '\0' };

    printf("'%s' -> %d\n", n1, htoi(n1));
    printf("'%s' -> %d\n", n2, htoi(n2));
    printf("'%s' -> %d\n", n3, htoi(n3));
    printf("'%s' -> %d\n", n4, htoi(n4));
}

// converts ascii string rep of hex number into a signed int
// precondition: s consists of valid hex chars
int htoi(const char s[]) {
   int i, num, result;

   i = 0;
   if (s[0] == '0' && s[1] == 'x') {
       i += 2;
   }

   result = 0;
   while (s[i] != '\0') {
       if (s[i] >= '0' && s[i] <= '9') {
           num = s[i] - '0';
       } else if (s[i] >= 'a' && s[i] <= 'e') {
           num = 10 + s[i] - 'a';
       } else if (s[i] >= 'A' && s[i] <= 'E') {
           num = 10 + s[i] - 'A';
       }
       result = result * 16 + num;
       i++;
   }

   return result;
}