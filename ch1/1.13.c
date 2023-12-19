#include <stdio.h>

#define MAX_WORD_LEN 50

// prints a histogram (horizontal and vertical) of the lengths of words in the input

int main(void) {
    int word_lens[MAX_WORD_LEN];

    // initialise word_lens frequencies to 0
    for (int i = 0; i < MAX_WORD_LEN; i++) {
        word_lens[i] = 0;
    }

    // populate word_lens frequencies array
    int c, count, longest, max_freq;
    count = longest = max_freq = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n' || c == ' ' || c == '\t') {
            if (count == 0) {
                continue;
            }
            if (count > longest) {
                longest = count;
            }
            word_lens[count]++;
            if (word_lens[count] > max_freq) {
                max_freq = word_lens[count];
            }
            count = 0;
        } else {
            count++;
        }
    }

    // print horizontal histogram
    printf("\nhorizontal histogram\n");
    for (int i = 1; i <= longest; i++) {
        printf("%d: ", i);
        for (int j = 0; j < word_lens[i]; j++) {
            putchar('#');
        }
        putchar('\n');
    }

    // print vertical histogram
    printf("\nvertical histogram\n");
    for (int i = max_freq; i > 0; i--) {
        for (int j = 1; j <= longest; j++) {
            if (word_lens[j] >= i) {
                putchar('#');
            } else {
                putchar(' ');
            }
            putchar(' ');
        }
        putchar('\n'); 
    }
    for (int i = 1; i <= longest; i++) {
        printf("%d ", i);
    }
    putchar('\n');

    return 0;
}