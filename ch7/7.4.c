#include <stdio.h>
#include <stdarg.h>

void minscanf(char *fmt, ...);

// usage example: ./a.out <<< "hello 1a 2.424 117 a8 4830"
int main(void) {
    int decimal;
    int octal;
    int hexadecimal;
    int unsigned_decimal;
    char character;
    char string[100];
    float floating_point;

    minscanf(
        "%s %d %c %f %o %x %u",
        string,
        &decimal,
        &character,
        &floating_point,
        &octal,
        &hexadecimal,
        &unsigned_decimal
    );

    printf("string: %s\n", string);
    printf("decimal: %d\n", decimal);
    printf("character: %c\n", character);
    printf("floating point: %f\n", floating_point);
    printf("octal: %o\n", octal);
    printf("hexadecimal: %x\n", hexadecimal);
    printf("unsigned: %u\n", unsigned_decimal);

    return 0;
}

// minimal scanf with variable argument list
void minscanf(char *fmt, ...) {
    va_list ap;
    char *p, *c, *s;
    int *i;
    unsigned *u;
    float *f;

    va_start(ap, fmt);  // point ap to first unnamed argument

    for (p = fmt; *p; p++) {
        if (*p != '%') continue;
        switch (*++p) {
            case 'd':   // integer
            case 'i':
                i = va_arg(ap, int *);
                scanf("%d", i);
                break;
            case 'e':   // float
            case 'f':
            case 'g':
                f = va_arg(ap, float *);
                scanf("%f", f);
                break;
            case 's':   // string
                s = va_arg(ap, char *);
                scanf("%s", s);
                break;
            case 'c':   // char
                c = va_arg(ap, char *);
                scanf("%c", c);
                break;
            case 'o':   // octal
                i = va_arg(ap, int *);
                scanf("%o", i);
                break;
            case 'x':   // hexadecimal
                i = va_arg(ap, int *);
                scanf("%x", i);
                break;
            case 'u':   // unsigned integer
                u = va_arg(ap, unsigned *);
                scanf("%u", u);
                break;
            default:
                break;
        }
    }

    va_end(ap); // clean up
}