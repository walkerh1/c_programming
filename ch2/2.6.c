#include <stdio.h>

unsigned set_bits(unsigned x, int p, int n, unsigned y);
void print_bits(unsigned x);

int main(void) {
    unsigned x = 0b01100011;
    unsigned y = 0b00011101;

    printf("x:\t\t");
    print_bits(x);

    printf("y:\t\t");
    print_bits(y);

    printf("res:\t");
    print_bits(set_bits(x, 4, 3, y));
}

// sets the n bits starting from position p in x (going right)
// to the bits in the same position in y.
// precondition: sizeof(unsigned) >= p >= n >= 0
unsigned set_bits(unsigned x, int p, int n, unsigned y) {
    // E.g. if p=4 and n=3 then mask will be: 0b1...11100011
    // all 1s excepts the n bits from position p are 0s.
    unsigned mask = (~0 << (p+1)) | ~(~0 << (p+1-n));

    // set the n bits starting from position p in x to 0.
    x &= mask;

    // isolate the n bits starting from position p in y, setting
    // every other bit to 0.
    y &= ~mask;

    // set the n bits starting from position p in x to the
    // bits in the same position in y.
    return x | y;
}

// utility for printing unsigned ints in binary format
void print_bits(unsigned x) {
    for (int i = 31; i >= 0; i--) {
        if (x >> i & 1) {
            putchar('1');
        } else {
            putchar('0');
        }
    }
    putchar('\n');
}