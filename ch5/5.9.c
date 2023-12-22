#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *month, int *day);

static char daytab[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main(void) {
    // test day_of_year
    printf("%d/%d/%d --> %d\n", 2023, 12, 22, day_of_year(2023, 12, 22));
    printf("%d/%d/%d --> %d\n", 2023, 9, 22, day_of_year(2023, 9, 22));
    printf("%d/%d/%d --> %d\n", 2020, 2, 29, day_of_year(2020, 2, 29));

    // test month_day
    int month, day;
    month_day(2020, 68, &month, &day);
    printf("%d (%d) --> %d/%d/%d\n", 68, 2020, 2020, month, day);
    month_day(2020, 366, &month, &day);
    printf("%d (%d) --> %d/%d/%d\n", 366, 2020, 2020, month, day);

    return 0;
}

// Convert (year, month, day) into number of days in year and return result.
int day_of_year(int year, int month, int day) {
    int leap;
    char *p;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    p = daytab[leap];

    while (--month) {
        day += *++p;
    }

    return day;
}

// From the number of days in the year so far, set month and day pointers to the appropriate values.
void month_day(int year, int yearday, int *month, int *day) {
    int i, leap;
    char *p;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    p = daytab[leap];

    while (yearday > *++p) {
        yearday -= *p;
    }

    // set month and day
    *month = (p - *(daytab + leap));
    *day = yearday;
}
