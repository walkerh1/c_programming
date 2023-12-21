#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 1000

int get_line(char s[], int lim);
int atoi(const char s[]);
double atof(const char s[]);
void reverse(char s[]);

// pointer arithmetic versions of get_line, atoi, atof, and reverse
int main(void) {
    char line[MAXLINE];

    // test get_line
    while ((get_line(line, MAXLINE)) > 1) {
        printf("%s", line);
    }

    // test atoi
    printf("%d\n", atoi("-25464"));
    printf("%d\n", atoi("  94382985"));

    // test atof
    printf("%f\n", atof("34.543"));
    printf("%.14f\n", atof("    -4.12432423424234"));

    // test reverse
    char s[] = "hello world";
    reverse(s);
    printf("%s --> %s\n", "hello world", s);

    return 0;
}

// get next line of input
int get_line(char s[], int lim) {
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

// converts ascii to int; no error handling
int atoi(const char s[]) {
    int n, sign;

    while (isspace(*s) && s++)
        ;

    sign = (*s == '-') ? -1 : 1;

    if (*s == '-' || *s == '+') {
        s++;
    }

    n = 0;
    while (isdigit(*s)) {
        n = 10 * n + (*s++ - '0');
    }

    return sign * n;
}

// convert ascii to double
double atof(const char s[]) {
    double val, power;
    int sign;

    while (isspace(*s) && s++)
        ;

    sign = (*s == '-') ? -1 : 1;

    if (*s == '+' || *s == '-') {
        s++;
    }

    for (val = 0.0; isdigit(*s); s++) {
        val = 10.0 * val + (*s - '0');
    }

    if (*s == '.') {
        s++;
    }

    for (power = 1.0; isdigit(*s); s++) {
        val = 10.0 * val + (*s - '0');
        power *= 10.0;
    }

    return sign * val / power;
}

// reverse
void reverse(char s[]) {
    char *t, tmp;
    for (t = s+strlen(s)-1; s < t; s++, t--) {
        tmp = *s;
        *s = *t;
        *t = tmp;
    }
}