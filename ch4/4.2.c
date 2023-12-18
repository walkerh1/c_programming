#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

double atof(char s[]);
int get_line(char line[], int max);

int main(void) {
    double sum;
    char line[MAXLINE];

    sum = 0;
    while (get_line(line, MAXLINE) > 0) {
        printf("\t%.10f\n", sum += atof(line));
    }

    return 0;
}

// convert ascii string to double
// precondition: s consists of valid floating point chars
double atof(char s[]) {
    double val, power;
    int i, sign, exp_sign, exp;

    // skip over leading whitespace
    for (i = 0; isspace(s[i]); i++)
        ;

    // determine sign of value
    sign = (s[i] == '+') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i++;
    }

    // get value up to decimal point
    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }

    // skip decimal point if there is one
    if (s[i] == '.') {
        i++;
    }

    // continue to update value; value is divided by power below
    // so multiplying by 10 once here corresponds to 1/10 below
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    // skip 'e' if it is there
    if (s[i] == 'e') {
        i++;
    }

    // get sign of exponent
    exp_sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '-') {
        i++;
    }

    // get exponent if there is one.
    for (exp = 0; isdigit(s[i]); i++) {
        exp = 10 * exp + (s[i] - '0');
    }

    // adjust power depending on sign of optional exponent
    for (int j = 0; j < exp; j++) {
        if (exp_sign > 0) {
            power /= 10; // move decimal point right one position
        } else {
            power *= 10; // move decimal point left one position
        }
    }

    // val / power readjusts where decimal point goes
    return sign * val / power;
}

// get line into s, return length
int get_line(char line[], int max) {
    int c, i;

    i = 0;
    while (--max > 0 && (c=getchar()) != EOF && c!='\n') {
        line[i++] = c;
    }
    if (c == '\n') {
        line[i++] = c;
    }
    line[i] = '\0';
    return i;
}
