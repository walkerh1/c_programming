#include <stdio.h>

#define ASCII 128

int main(void) {
    int char_freqs[ASCII];

    for (int i = 0; i < ASCII; i++) {
        char_freqs[i] = 0;
    }    
    
    int c;
    int max_freq = 0;
    while ((c = getchar()) != EOF) {
        char_freqs[c]++;
        if (char_freqs[c] > max_freq) {
            max_freq = char_freqs[c];
        }
    }

    printf("\ncharacter frequencies\n");
    for (int i = 0; i < ASCII; i++) {
        if (char_freqs[i] == 0) continue;
        if (i == '\n') printf("'\\n': ");
        else if (i == '\t') printf("'\\t': ");
        else printf(" '%c': ", i);
        for (int j = 0; j < char_freqs[i]; j++) {
            putchar('#');
        }
        putchar('\n');
    }

    return 0;
}