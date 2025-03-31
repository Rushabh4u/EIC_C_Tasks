/*
 * Program: Error check in day_of_year and month_day with Pointers
 * Author: [Your Name]
 * Created Date: [Date]
 * Description: This program contains two functions:
 *              - day_of_year: Given a year, month, and day, it returns the day of the year.
 *              - month_day: Given a year and day of the year, it returns the month and day.
 *              The program uses pointers instead of array indexing and performs error checks for invalid inputs.
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
    int leap;
    char *month_ptr;
    /* Check if it's a leap year */
    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

    /* Error check: Invalid year, month, or day */
    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return -1;  /* Return -1 if the date is invalid */
    }

    /* Get the pointer to the month tab for the correct year type (common or leap year) */
    month_ptr = &daytab[leap][1];  /* Pointer to the first month (January) */

    /* Error check for invalid day based on month */
    if (day > *(month_ptr + month - 1)) {
        return -1;  /* Invalid day */
    }

    /* Traverse through the months before the given month to sum up the days */
    for (int i = 1; i < month; i++) {
        day += *(month_ptr + i - 1);  /* Add the days of the previous months */
    }

    return day;  /* Return the day of the year */
}
