#ifndef QUERY_PERSON_SUMMARY_H
#define QUERY_PERSON_SUMMARY_H

#include "./data/database.h"

typedef struct query_person_summary Query_person_summary;

/**
 * @brief Initializes "Query_person_summary" variable.
 *
 * @return The initialized variable.
 */
Query_person_summary* initialize_query_person_summary();

/**
 * @brief Frees the memory allocated for the "Query_person_summary" variable.
 *
 * @param query_person_summary The variable to be freed.
 */
void free_person_summary(void* struct_to_free);

/**
 * @brief Gets the information from the query.
 * 
 * @param to_array_string The struct to transform into acessible information.
 * 
 * @return char* Readble information.
 */
char** person_summary_iterator(void* void_to_array_string, int num_to_print);

/**
 * @brief Formats the user summary into a string.
 * 
 * @param user The user object.
 * 
 * @return char* A string with the formatted user summary.
 */
Query_person_summary* format_user_summary(User* user);

/**
 * @brief Formats the artist summary into a string.
 * 
 * @param db The database.
 * @param artist The artist object.
 * 
 * @return char* A string with the formatted artist summary.
 */
Query_person_summary* format_artist_summary(ArtistsCatalog* catalog, Artist* artist);

/**
 * @brief Gets the user summary.
 * 
 * @param db The database.
 * @param user_id The user ID.
 * 
 * @return char* The user summary.
 */
int query_person_summary(void** to_fill, DataBase* db, char* user_id);


#endif // QUERY_PERSON_SUMMARY_H