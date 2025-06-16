#ifndef QUERY_ARTIST_DISCOGRAPHY_H
#define QUERY_ARTIST_DISCOGRAPHY_H

#include "./data/database.h"

/**
 * @brief Frees the memory allocated for the artist discography query.
 *
 * This function takes a pointer to the memory that needs to be freed and 
 * releases the allocated resources to prevent memory leaks.
 *
 * @param to_free Pointer to the memory to be freed.
 */
void free_query_artist_discography(void* to_free);

/**
 * @brief Iterates over the artist discography and returns an array of strings.
 *
 * This function takes a pointer to the artist discography and the number of 
 * entries to print, and returns an array of strings representing the discography.
 *
 * @param void_to_array_string Pointer to the artist discography.
 * @param num_to_print Number of entries to print.
 * 
 * @return char** Array of strings representing the artist discography.
 */
char** artist_discography_iterator(void* void_to_array_string, int num_to_print);

/**
 * @brief Gets the N biggest discographys by country if specified.
 * 
 * @param to_fill Specific struct to be filled.
 * @param database Database.
 * @param input Query 2 input.
 * 
 * @return char* Artists with the N biggest discographys , by country if specified.
 */
int query_artist_discography(void** to_fill, DataBase* database, char* input);

#endif // QUERY_ARTIST_DISCOGRAPHY_H