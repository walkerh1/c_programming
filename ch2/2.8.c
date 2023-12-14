#include <stdio.h>

#define UNSIGNED_NUM_BITS 32

unsigned right_rot(unsigned x, int n);
void print_bits(unsigned x);

int main(void) {
    unsigned x = 0b01100011;
    printf("x:\t\t");
    print_bits(x);
    printf("res:\t");
    print_bits(right_rot(x, 4));
    printf("\t\t(rotate right by 4 positions)\n");

    unsigned y = 0b11110111;
    printf("\ny:\t\t");
    print_bits(y);
    printf("res:\t");
    print_bits(right_rot(y, 7));
    printf("\t\t(rotate right by 7 positions)\n");

    return 0;
}

// return x rotated to the right by n bit positions.
unsigned right_rot(unsigned x, int n) {
    // shift last n bits of x left to the most significant positions
    // and shift x right n bits to move rest of the bits into less
    // significant positions, then bitwise-or the results. Note we are
    // relying on right shift always pushing 0s onto the left of the
    // sequence, which is always true for signed ints.
    return (x << (UNSIGNED_NUM_BITS-n)) | (x >> n);
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
