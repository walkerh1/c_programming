#include <stdio.h>
#include <string.h>

#define MAXLINES 1000       // max number of any line to be sorted
#define MAXSTORAGE 10000    // number of bytes available for storage
#define MAXLEN 1000         // max length of any input line

int readlines(char *lineptr[], char *linestore, int maxlines);
int get_line(char *s, int lim);
void writelines(char *lineptr[], int nlines);
void qsort(char *v[], int left, int right);
int partition(char *v[], int left, int right);
void swap(char *v[], int i, int j);

// read lines from stdin, sort lines, write lines to stdout
int main(void) {
    int nlines;
    char linestore[MAXSTORAGE]; // storage
    char *lineptr[MAXLINES];    // array of pointers to chars

    if ((nlines = readlines(lineptr, linestore, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big\n");
        return 1;
    }
}

// read input lines into array of pointers
int readlines(char *lineptr[], char *linestore, int maxlines) {
    int len, nlines;
    char line[MAXLEN];
    char *p = linestore;                // init p to beginning of available storage
    char *storelim = p + MAXSTORAGE;    // where storage ends

    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || p + len > storelim) {
            // either exceeded max lines or exceeded max storage
            return -1;
        } else {
            line[len-1] = '\0'; // deletes trailing newline
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
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
void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
}

// sort lines using quicksort algorithm
void qsort(char *v[], int left, int right) {
    if (left >= right) {
        return;
    }
    int p = partition(v, left, right);
    qsort(v, left, p-1);
    qsort(v, p+1, right);
}

// split v into elements < partition on the left and elements >= part on the right; return index of partition
int partition(char *v[], int left, int right) {
    int i, part;
    // just choose right as partition
    for (i = left, part = left; i < right; i++) {
        if (strcmp(v[i], v[right]) < 0) {
            swap(v, part++, i);
        }
    }
    swap(v, part, right);
    return part;
}

// swap elements i and j in v;
void swap(char *v[], int i, int j) {
    char *tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}