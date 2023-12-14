#include <stdio.h>

#define UNSIGNED_NUM_BITS 32

unsigned bit_count(int x);
void print_bits(unsigned x);

int main(void) {
    int x = 0b01100011;
    printf("x:\t\t(%d)\t", x);
    print_bits(x);
    printf("res:\t%u\n", bit_count(x));

    int y = 0b11110111;
    printf("\ny:\t\t(%d)\t", y);
    print_bits(y);
    printf("res:\t%u\n", bit_count(y));

    int z = 0b11000000;
    printf("\nz:\t\t(%d)\t", z);
    print_bits(z);
    printf("res:\t%u\n", bit_count(z));

    int u = -42;
    printf("\nu:\t\t(%d)\t", u);
    print_bits(u);
    printf("res:\t%u\n", bit_count(u));

    return 0;
}

// count the number of 1-bits in x.
unsigned bit_count(int x) {
    // We rely on the fact that x &= (x-1) deletes the rightmost 1-bit in x.
    // Why does this work? If the rightmost 1-bit in x is at position i, then
    // the bit at position i in (x-1) has to be a 0-bit. So masking x with (x-1)
    // will turn the rightmost 1-bit of x into a 0-bit. E.g. if x == 0b0110
    // (i.e. 10), then x-1 == 0b0101 (i.e. 9), and so x & (x-1) == 0b0100 deletes
    // the rightmost 1-bit of x.
    //
    // Twos complement means this will work for signed integers as well. E.g.
    // suppose x == -10; which in twos complement is 0b1010 (got by flipping
    // the bits in 0b0110 (i.e. 10) and adding 0b0001); then x-1 == -11, which
    // in twos complement is 0b1001 (got from adding -1 to -10, which in binary
    // is 0b1010 + 0b1111 == 0b1001); and so x & (x-1) == 0b1000 deletes the
    // rightmost 1-bit of x, as desired.
    //
    // If signed ints were represented by using the most significant bit as a sign
    // bit, this wouldn't work. E.g. -10 would be represented as 0b10000110 and -11
    // would be 0b10000111. But 0b10000110 & 0b10000111 = 0b10000110, which is just
    // -10, so we don't get the desired property of the rightmost 1-bit being deleted.

    int one_bits = 0;
    while (x) {
        x &= (x-1);
        one_bits++;
    }
    return one_bits;
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
