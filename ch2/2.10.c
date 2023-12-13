#include <stdio.h>

int lower(int c);

int main(void) {
  printf("\'A\' ==> \'%c\'\n", lower('A'));
  printf("\'b\' ==> \'%c\'\n", lower('b'));
  printf("\'C\' ==> \'%c\'\n", lower('C'));
  return 0;
}

int lower(int c) {
  return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}