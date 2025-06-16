#ifndef QUERY_GENRES_BY_AGE_GROUP_H
#define QUERY_GENRES_BY_AGE_GROUP_H

#include "./data/database.h"
/**
 * @brief Generates an array of genre strings based on age group.
 *
 * This function takes a pointer to an array of strings and an integer specifying
 * the number of genres to print. It returns an array of genre strings filtered
 * by the specified age group.
 *
 * @param void_to_array_string A pointer to an array of strings representing genres.
 * @param num_to_print An integer specifying the number of genres to print.
 * @return A dynamically allocated array of strings containing the genres filtered by age group.
 */

char** genre_by_age_group_iterator(void* void_to_array_string, int num_to_print);

/**
 * @brief Gets the genres and the number of likes for a specific age group.
 * 
 * @param db The database.
 * @param input The input string.
 * 
 * @return char* Genres and the number of likes for a specific age group.
 */
int query_genre_by_age_group(void** to_fill, DataBase* db, char* input);

/**
 * @brief Frees the memory allocated for the query genres by age group.
 * 
 * @param to_free The pointer to the memory to be freed.
 */
void free_query_genres_by_age_group(void* to_free);

#endif // QUERY_GENRES_BY_AGE_GROUP_H