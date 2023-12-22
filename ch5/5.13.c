#include <stdio.h>
#include <stdlib.h>

#define DEFAULTN 10 // default number of lines to print
#define MAXN 100    // largest possible n
#define MAXLINE 100 // max length of a line

int get_line(char *s, int lim);

// tail: print the last n lines of input. Solution uses a ring buffer to store the most
// recently read n lines of input. At the end of input, the last n lines will be whatever's
// left over in the ring buffer. Solution doesn't use a pointer array to store lines, as
// is suggested in the problem statement, though it doesn't use a fixed 2D array either.
// Instead, it allocates a 1D block of memory that is big enough to store n lines of
// MAXLINE bytes each, and uses pointer arithmetic to navigate the block as if it were a
// 2D array. There is some memory wasted when lines are less than MAXLINE long. But the
// alternative would be to malloc each line that's read, which would incur a huge time cost
// as the number of input lines increases.
int main(int argc, char *argv[]) {
    int n, len;
    char *buf_start, *head, *tail;

    // determine n
    if (argc == 1) {
        n = DEFAULTN;
    } else if (argc == 2 && **++argv == '-') {
        n = atoi(*argv + 1);
    } else {
        printf("usage: tail [-n]\n");
        exit(1);
    }

    // make sure n is reasonable
    if (n < 1 || n > MAXN) {
        n = MAXN;
    }

    // allocate space for an array of n * MAXLINE chars
    len = n * MAXLINE * sizeof(char);
    if ((buf_start = (char *)malloc(len)) == NULL) {
        printf("error allocating memory\n");
        exit(1);
    }

    // read lines into the ring buffer
    head = tail = buf_start;
    while (get_line(tail, MAXLINE) != EOF) {
        if (tail + MAXLINE == buf_start + len) {
            // loop back to start of buffer when we reach the end
            tail = buf_start;
        } else {
            // else just increment to next line in buffer
            tail += MAXLINE;
        }

        // once buffer is full, tail will always equal head after incrementing tail
        if (tail == head) {
            if (head + MAXLINE == buf_start + len) {
                head = buf_start;
            } else {
                head += MAXLINE;
            }
        }
    }

    // print buffer starting from head
    char *p = head;
    while (p != tail) {
        printf("%s", p);
        if (p + MAXLINE == buf_start + len) {
            p = buf_start;
        } else {
            p += MAXLINE;
        }
    }
    printf("%s", p);

    return 0;
}

// get next line of input; returns last read in char (useful to detect EOF)
int get_line(char *s, int lim) {
    int c, i;
    for (i=0; i<lim-1 && (c = getchar()) != EOF && c!='\n'; i++) {
        *(s+i) = c;
    }
    if (c == '\n') {
        *(s+i) = '\n';
        i++;
    }
    *(s+i) = '\0';
    return c;
}