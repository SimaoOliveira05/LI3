#ifndef TIME_H
#define TIME_H

#include <time.h>

/**
 * @brief Retrieves the date from a timestamp.
 * 
 * @param timestamp timestamp of type "yyyy/mm/dd hh:mm:ss".
 * @param date The date string (yyyy/mm/dd) to be filled.
 */
void get_date(const char* timestamp, char* date);

/**
 * @brief Get the time from a timestamp.
 * 
 * @param timestamp timestamp of type "yyyy/mm/dd hh:mm:ss".
 * @param time The time string (hh:mm:ss) to be filled.
 */
void get_time(const char* timestamp, char* time);

/**
 * @brief Get the year from a date string.
 * 
 * @param date_str The date string (yyyy/mm/dd).
 * @param year The year string (yyyy) to be filled.
 */
void get_year(const char* date_str, char* year);

/**
 * @brief Converts a time string to seconds.
 * 
 * @param time The time string (hh:mm:ss).
 * 
 * @return int The time in seconds.
 */
int convert_time_to_seconds(char* time);

/**
 * @brief Converts seconds to a time string.
 * 
 * @param total_seconds The time in seconds.
 * 
 * @return char* The time string (hh:mm:ss).
 */
char* convert_seconds_to_time(int total_seconds);

/**
 * @brief Get the week offset from a time string based on a reference date.
 * The chosen reference date is the abstract date 0th of first year (0001/01/00).
 * Every date between 0001/01/06 (first sunday of the calendar) and 0001/01/12, returns 1, between 0001/01/13 and 0001/01/19 returns 2, and so on.
 * 
 * @param time The time string (yyyy/mm/dd).
 * 
 * @return int The week offset.
 */
int get_week_offset(char* time);

#endif