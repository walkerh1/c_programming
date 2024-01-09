#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

int main(void) {
    int i = 20;
    unsigned u = 2000;
    char c = 'a';
    double d = 3.1415;
    minprintf(
            "%s %d %i %f %g %e %c %o %x %u",
            "hello",
            i,
            i,
            d,
            d,
            d,
            c,
            i,
            i,
            u
    );

    return 0;
}

// minimal printf with variable argument list
void minprintf(char *fmt, ...) {
    va_list ap;
    char *p, *sval;
    int ival, cval;
    double dval;

    va_start(ap, fmt);  // point ap to first unnamed argument

    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':   // integer
            case 'i':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':   // floating point
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 'g':   // floating point
            case 'G':
                dval = va_arg(ap, double);
                printf("%g", dval);
                break;
            case 'e':   // floating point
            case 'E':
                dval = va_arg(ap, double);
                printf("%e", dval);
                break;
            case 's':   // string
                for (sval = va_arg(ap, char *); *sval; sval++) {
                    putchar(*sval);
                }
                break;
            case 'c':   // char
                cval = va_arg(ap, int);
                printf("%c", cval);
                break;
            case 'o':   // octal
                ival = va_arg(ap, int);
                printf("%o", ival);
                break;
            case 'x':   // hexadecimal
            case 'X':
                ival = va_arg(ap, int);
                printf("%x", ival);
                break;
            case 'u':   // unsigned integer
                ival = va_arg(ap, int);
                printf("%u", ival);
                break;
            default:
                putchar(*p);
                break;
        }
    }

    va_end(ap); // clean up
}
