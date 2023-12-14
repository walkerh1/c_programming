#include <stdio.h>

#define UNSIGNED_NUM_BITS 32

unsigned invert(unsigned x, int p, int n);
void print_bits(unsigned x);

int main(void) {
    unsigned x = 0b01100011;
    printf("x:\t\t");
    print_bits(x);
    printf("res:\t");
    print_bits(invert(x, 4, 3));
    printf("\t\t(3 bits from position 4)\n");

    unsigned y = 0b01110111;
    printf("\ny:\t\t");
    print_bits(y);
    printf("res:\t");
    print_bits(invert(y, 5, 4));
    printf("\t\t(4 bits from position 5)\n");

    return 0;
}

// return x with the n bits starting at position p flipped
// precondition: sizeof(unsigned) >= p >= n >= 0
unsigned invert(unsigned x, int p, int n) {
    // E.g. if p=4 and n=3 then mask will be: 0b1...11100011,
    // all 1s excepts the n bits from position p are 0s.
    unsigned mask = (~0 << (p+1)) | ~(~0 << (p+1-n));

    // invert x, then isolate the n bits starting from position p
    // in x, setting every other bit to 0.
    unsigned inverted = ~x & ~mask;

    // set the n bits starting from position p in x to 0.
    x &= mask;

    // set the n bits starting from position p in x to the
    // bits in the same position in inverted, which are the
    // flipped bits of the original.
    return x | inverted;
}

// utility for printing unsigned ints in binary format
void print_bits(unsigned x) {
    for (int i = UNSIGNED_NUM_BITS-1; i >= 0; i--) {
        if (x >> i & 1) {
            putchar('1');
        } else {
            putchar('0');
        }
    }
    putchar('\n');
}
