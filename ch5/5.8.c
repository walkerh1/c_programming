#include <stdio.h>

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *month, int *day);

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main(void) {
    // test day_of_year
    printf("%d/%d/%d --> %d\n", 2023, 12, 22, day_of_year(2023, 12, 22));
    printf("%d/%d/%d --> %d\n", 2023, 13, 22, day_of_year(2023, 13, 22));
    printf("%d/%d/%d --> %d\n", 2020, 2, 30, day_of_year(2020, 2, 30));

    // test month_day
    int month, day;
    month_day(2020, 68, &month, &day);
    printf("%d (%d) --> %d/%d/%d\n", 68, 2020, 2020, month, day);
    month_day(2020, 366, &month, &day);
    printf("%d (%d) --> %d/%d/%d\n", 366, 2020, 2020, month, day);
    printf("%d (%d) --> %d\n", 366, 2021, month_day(2021, 366, &month, &day));

    return 0;
}

// Convert (year, month, day) into number of days in year; return this number or
// -1 if any of year, month, day are invalid.
int day_of_year(int year, int month, int day) {
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    // check we got a valid month
    if (month < 1 || month > 12) {
        return -1;
    }

    // check we got a valid day of the month
    if (day < 1 || day > daytab[leap][month]) {
        return -1;
    }

    // calculate days in year so far
    for (i = 1; i < month; i++) {
        day += daytab[leap][i];
    }

    return day;
}

// From the number of days in the yearday, set month and day pointers to the appropriate
// values; return 0 if success, and -1 if the year or yearday is invalid.
int month_day(int year, int yearday, int *month, int *day) {
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    // check we got a valid yearday
    if (yearday < 1 || (leap && yearday > 366) || (!leap && yearday > 365)) {
        return -1;
    }

    // count months that go into yearday; remainder is day
    for (i = 1; yearday > daytab[leap][i]; i++) {
        yearday -= daytab[leap][i];
    }

    // set month and day
    *month = i;
    *day = yearday;

    return 0;
}
