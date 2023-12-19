#include <stdio.h>

// verify that `getchar() != 0` evaluates to 0 or 1

int main(void) {
    int c;
    printf("'getchar() != 0' evaluates to %d\n", getchar() != EOF);
    return 0;
}