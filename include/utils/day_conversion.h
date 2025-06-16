#ifndef DAY_CONVERSION_H
#define DAY_CONVERSION_H

/**
 * @brief Returns the day of the year given the month and day.
 *
 * This function calculates the day of the year based on the given month and day.
 *
 * @param month The month (1-12).
 * @param day The day (1-31).
 * @return The day of the year (1-365) or -1 for invalid inputs.
 */
int day_of_year(int month, int day);

/**
 * @brief Converts the day of the year to month and day.
 *
 * This function converts a day of the year to the corresponding month and day.
 *
 * @param day_of_year The day of the year (1-365).
 * @param month Pointer to store the resulting month.
 * @param day Pointer to store the resulting day.
 */
void month_day(int day_of_year, int* month, int* day);

#endif