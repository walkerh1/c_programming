#include <stdio.h>

// print a celsius-to-fahrenheit conversion table

int main(void) {
    float fahr, celsius;
    int lower, upper, step;

    lower = -20;
    upper = 150;
    step = 10;

    printf("Cels  Fahr\n");
    celsius = lower;
    while (celsius <= upper) {
        fahr = ((9.0/5.0) * celsius) + 32.0;
        printf("%4.0f %6.1f\n", celsius, fahr);
        celsius += step;
    }

    return 0;
}