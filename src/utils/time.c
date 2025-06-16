#include "./utils/time.h"
#include "./utils/strsep_by_token.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include <string.h>

// Optimized function to extract year from a date string
void get_year(const char* date_str, char* year) {
    // Directly copy 4 characters without dynamic memory allocation
    memcpy(year, date_str, 4);
    year[4] = '\0';
}

// Optimized function to extract date
void get_date(const char* timestamp, char* date) {
    // Directly copy 10 characters without dynamic memory allocation
    memcpy(date, timestamp, 10);
    date[10] = '\0';
}

// Optimized function to extract time
void get_time(const char* timestamp, char* time) {
    // Directly copy 8 characters without dynamic memory allocation
    memcpy(time, timestamp + 11, 8);
    time[8] = '\0';
}


int convert_time_to_seconds(char* time) {
    int hours = 0, minutes = 0, seconds = 0;
    char* time_copy = strdup(time);
    strsep_by_token(&hours, &minutes, &seconds, ":", time_copy);
    free(time_copy);
    return hours * 3600 + minutes * 60 + seconds;
}


char* convert_seconds_to_time(int total_seconds) {
    if (total_seconds < 0) {
        return NULL; // Return NULL for negative input
    }
    
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    // Allocate memory for the result string
    char* time_str = (char*)malloc(13 * sizeof(char)); // HH:MM:SS is 8 characters + null terminator

    if (time_str != NULL) {
        // Format the string
        snprintf(time_str, 13, "%02d:%02d:%02d", hours, minutes, seconds);
    }

    return time_str;
}

int is_leap_year(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 1 : 0;
}

int get_day_of_year(int day, int month, int year) {
    // Precomputed cumulative day counts for each month (non-leap year)
    static const int cumulative_days[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    
    // Calculate the base day of the year
    int day_of_year = cumulative_days[month - 1] + day;
    
    // Add one day if it's a leap year and the month is after February
    if (is_leap_year(year) && month > 2)
        day_of_year += 1;
    
    return day_of_year;
}

int get_week_offset(char* time) {

    if (time == NULL) return -1;

    int day, month, year;
    sscanf(time, "%d/%d/%d", &year, &month, &day);

    // Calculate the number of leap years and non-leap years and get the day of the year
    int last_year = year - 1;
    int leap_years = last_year / 4 - last_year / 100 + last_year / 400;
    int non_leap_years = last_year - leap_years;
    int day_of_year = get_day_of_year(day, month, year);

    // Calculate total days between the initial calendar date and the input date
    int total_days = leap_years * 366 + non_leap_years * 365 + day_of_year;

    // Calculate the week offset
    int week_offset = total_days / 7;

    return week_offset;
}