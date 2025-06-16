#ifndef QUERY_ARTIST_ON_TOP_10_H
#define QUERY_ARTIST_ON_TOP_10_H

#include "./data/database.h"

/**
 * @brief Function to free the memory allocated to print the query result.
 * 
 * @param struct_to_free The struct to free.
 */
void free_artist_on_top_10_more_often(void* struct_to_free);

/**
 * @brief Gets the information from the query.
 * 
 * @param void_to_array_string The struct to iterate.
 * @param num_to_print The number of elements to print.
 * 
 * @return char** Readble information.
 */
char** artist_on_top_10_more_often_iterator(void* void_to_array_string, int num_to_print);

/**
 * @brief Get the artist id of the artist that is more often on the top 10.
 * 
 * @param artistsCatalog The artists catalog.
 * @param timesOnTop10 The number of times the artist is on the top 10.
 * @return int The artist id.
 */
int top_10_more_often_artist_id(ArtistsCatalog* artistsCatalog, int* timesOnTop10);


/**
 * @brief Query 4: Get the artist that is more often on the top 10.
 * 
 * @param database The database.
 * @param input The input.
 * 
 * @return char* The result of the query.
 */
int  query_artist_on_top_10(void** to_fill, DataBase* database, char* input);

#endif // QUERY_ARTIST_ON_TOP_10_H