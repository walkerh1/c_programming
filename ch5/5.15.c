#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000    // max number of input lines read
#define MAXLEN 1000     // max length of a line

char *lineptr[MAXLINE]; // pointers to the text lines

int readlines(char *lineptr[], int maxline);
void writelines(char *lineptr[], int maxline);
void quicksort(void *v[], int left, int right, int (*comp)(void *, void *), int reverse);
int numcmp(const char *s1, const char *s2);
int ignorecasecmp(const char *s1, const char *s2);

int main(int argc, char *argv[]) {
    int nlines;
    int numeric = 0, reverse = 0, fold = 0;
    char c;
    int (*comp)(const char *s1, const char *s2);

    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    reverse = 1;
                    break;
                case 'f':
                    fold = 1;
                    break;
                default:
                    printf("Illegal option: %c\n", c);
                    argc = -1;
                    break;
            }
        }
    }

    if (argc != 0) {
        printf("Usage: sort -[nr]\n");
        return 1;
    }

    if ((nlines = readlines(lineptr, MAXLINE)) >= 0) {
        comp = numeric ? numcmp : fold ? ignorecasecmp : strcmp;
        quicksort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) comp, reverse);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

void quicksort(void *v[], int left, int right, int (*comp) (void *, void *), int r) {
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right) {
        return;
    }

    int reverse = r ? -1 : 1;

    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) * reverse < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    quicksort(v, left, last-1, comp, r);
    quicksort(v, last+1, right, comp, r);
}

int numcmp(const char *s1, const char *s2) {
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    } else {
        return 0;
    }
}

int ignorecasecmp(const char *s1, const char *s2) {
    int i = 0;
    char x, y;
    int diff = 'a' - 'A';
    while (s1[i] != '\0' && s2[i] != '\0') {
        x = (s1[i] >= 'A' && s1[i] <= 'Z') ? s1[i] + diff : s1[i];
        y = (s2[i] >= 'A' && s2[i] <= 'Z') ? s2[i] + diff : s2[i];
        if (x < y) {
            return -1;
        } else if (x > y) {
            return 1;
        }
        i++;
    }
    return 0;
}

void swap(void *v[], int i, int j) {
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// read input lines into array of pointers
int readlines(char *lineptr[], int maxline) {
    int get_line(char *, int);

    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxline || (p = (char *)malloc(len+1)) == NULL) {
            // either exceeded max lines or malloc couldn't enough find space
            return -1;
        } else {
            line[len-1] = '\0'; // deletes trailing newline
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

// get next line of input
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
    return i;
}

// write lines to stdout
void writelines(char *lineptr[], int maxline) {
    while (maxline-- > 0) {
        printf("%s\n", *lineptr++);
    }
}
