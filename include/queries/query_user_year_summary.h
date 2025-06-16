#ifndef QUERY_USER_YEAR_SUMMARY_H
#define QUERY_USER_YEAR_SUMMARY_H

#include "./data/database.h"

/**
 * @brief Frees the memory allocated for the user year summary structure.
 *
 * @param struct_to_free Pointer to the structure to be freed.
 */
void free_query_user_year_summary(void* struct_to_free);

/**
 * @brief Iterates over the user year summary and returns an array of strings.
 *
 * @param void_to_array_string Pointer to the structure containing the user year summary.
 * @param num_to_print Number of strings to be printed.
 * @return Array of strings representing the user year summary.
 */
char** user_year_summary_iterator(void* void_to_array_string, int num_to_print);

/**
 * @brief Generates a summary of a user's activity for a given year.
 *
 * This function processes the input to generate a summary of a user's activity for a specified year.
 * It retrieves the user's history, calculates various statistics, and formats them into an output structure.
 *
 * @param to_fill Pointer to the output structure to be filled with the summary data.
 * @param db Pointer to the database.
 * @param input The input query string.
 * @return An integer representing the status of the operation.
 */
int query_user_year_summary(void** to_fill, DataBase* db, char* input);

#endif