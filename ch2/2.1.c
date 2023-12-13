#include <limits.h>
#include <stdio.h>

int main(void) {
    printf("char:\t\t\t\t%lu byte\t[%d, %d]\n", sizeof(char), SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char:\t\t%lu byte\t[%d, %u]\n", sizeof(unsigned char), 0, UCHAR_MAX);
    printf("short:\t\t\t\t%lu bytes\t[%d, %d]\n", sizeof(short), SHRT_MIN, SHRT_MAX);
    printf("unsigned short:\t\t%lu bytes\t[%d, %u]\n", sizeof(unsigned short), 0, USHRT_MAX);
    printf("int:\t\t\t\t%lu bytes\t[%d, %d]\n", sizeof(int), INT_MIN, INT_MAX);
    printf("unsigned int:\t\t%lu bytes\t[%d, %u]\n", sizeof(unsigned int), 0, UINT_MAX);
    printf("long:\t\t\t\t%lu bytes\t[%ld, %ld]\n", sizeof(long), LONG_MIN, LONG_MAX);
    printf("unsigned long:\t\t%lu bytes\t[%d, %lu]\n", sizeof(unsigned long), 0, ULONG_MAX);
    printf("long long:\t\t\t%lu bytes\t[%lld, %lld]\n", sizeof(long long), LONG_LONG_MIN, LONG_LONG_MAX);
    printf("unsigned long long:\t%lu bytes\t[%d, %llu]\n", sizeof(unsigned long long), 0, ULONG_LONG_MAX);

    printf("float:\t\t\t\t%lu bytes\n", sizeof(float));
    printf("double:\t\t\t\t%lu bytes\n", sizeof(double));
    printf("long double:\t\t%lu bytes\n", sizeof(long double));
    return 0;
}