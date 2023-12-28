#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 1000    // max number of input lines read
#define MAXLEN 1000     // max length of a line

char *lineptr[MAXLINE]; // pointers to the text lines

int readlines(char *lineptr[], int maxline);
void writelines(char *lineptr[], int maxline);
void quicksort(void *v[], int left, int right, int (*comp)(void *, void *));
int numcmp(const char *s1, const char *s2);
int charcmp(const char *s1, const char *s2);

int numeric = 0;    // numeric sort
int reverse = 0;    // decreasing order
int fold = 0;       // fold: ignore case
int dir = 0;        // directory order: only sort on alphabet, number and blank space

int main(int argc, char *argv[]) {
    int nlines;
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
                case 'd':
                    dir = 1;
                    break;
                default:
                    printf("Illegal option: %c\n", c);
                    argc = -1;
                    break;
            }
        }
    }

    if (argc != 0) {
        printf("Usage: sort -[dfnr]\n");
        return 1;
    }

    if ((nlines = readlines(lineptr, MAXLINE)) >= 0) {
        quicksort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) (numeric ? numcmp : charcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

// quicksort algorithm that can reverse order
void quicksort(void *v[], int left, int right, int (*comp) (void *, void *)) {
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right) {
        return;
    }

    int rev = reverse ? -1 : 1;

    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) * rev < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    quicksort(v, left, last-1, comp);
    quicksort(v, last+1, right, comp);
}

// custom number comparator
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

// custom char comparator that depends on options passed to command line
int charcmp(const char *s1, const char *s2) {
    int i, j;
    char x, y;

    i = j = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (dir) {
            while (!isalnum(s1[i]) && s1[i] != ' ' && s1[i] != '\0') {
                i++;
            }
            while (!isalnum(s2[j]) && s2[j] != ' ' && s2[j] != '\0') {
                j++;
            }
        }
        x =  fold ? tolower(s1[i]) : s1[i];
        y =  fold ? tolower(s2[j]) : s2[j];
        if (x < y) {
            return -1;
        } else if (x > y) {
            return 1;
        }
        i++;
        j++;
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
