/*
 * Program: Error check in day_of_year and month_day with User Input
 * Author: 164993_faizan_momin
 * Created Date: 17/12/2024
 * Description: This program contains two functions:
 *              - day_of_year: Given a year, month, and day, it returns the day of the year.
 *              - month_day: Given a year and day of the year, it returns the month and day.
 *              The program performs error checks for invalid inputs, and takes user input.
 */

#include <stdio.h>

/* Array to store the number of days in each month for both common and leap years */
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},  /* Common year */
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}   /* Leap year */
};

/* Function prototypes */
int day_of_year(int year, int month, int day);   /* Get the day of the year */

int main(void) {
    int year, month, day, yearday;

    /* Get user input for the year, month, and day */
    printf("Enter year: ");
    if (scanf("%d", &year) != 1) {
        printf("Invalid input for year\n");
        return 1;
    }

    printf("Enter month: ");
    if (scanf("%d", &month) != 1) {
        printf("Invalid input for month\n");
        return 1;
    }

    printf("Enter day: ");
    if (scanf("%d", &day) != 1) {
        printf("Invalid input for day\n");
        return 1;
    }

    /* Call day_of_year function */
    yearday = day_of_year(year, month, day);
    if (yearday == -1) {
        printf("Invalid date!!");
        return -1;
    } else {
        printf("%d-%d is %dth day of %d\n",day,month,yearday,year);
    }
    return 0;
}

/* day_of_year: Given a year, month, and day, return the day of the year */
int day_of_year(int year, int month, int day) {
    int i, leap;

    /* Check if it's a leap year */
    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

    /* Error check: Invalid year, month, or day */
    if (year < 1 || month < 1 || month > 12 || day < 1 || day > daytab[leap][month]) {
        return -1;  /* Return -1 if the date is invalid */
    }

    /* Sum the days of the months before the given month */
    for (i = 1; i < month; i++) {
        day += daytab[leap][i];
    }

    return day;  /* Return the day of the year */
}
