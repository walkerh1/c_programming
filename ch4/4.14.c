#include <stdio.h>

#define swap(t, x, y) { t tmp = x; x = y; y = tmp; }

int main(void) {
    int a, b;
    a = 1;
    b = 4;
    printf("before:\tx = %d   y = %d\n", a, b);
    swap(int, a, b);
    printf("after:\tx = %d   y = %d\n", a, b);

    return 0;
}