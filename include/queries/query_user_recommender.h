#ifndef QUERY_USER_recommender_H
#define QUERY_USER_recommender_H

#include "./data/database.h"



/**
 * @brief Frees the memory allocated for the query user recommender structure.
 *
 * This function takes a pointer to the structure to be freed and releases the memory
 * allocated for it.
 *
 * @param struct_to_free A pointer to the structure to be freed.
 */
void free_query_user_recommender(void* struct_to_free);

/**
 * @brief Generates an array of recommended users.
 *
 * This function takes a pointer to an array of strings and an integer specifying
 * the number of recommendations to print. It returns an array of recommended users.
 *
 * @param void_to_array_string A pointer to an array of strings.
 * @param num_to_print The number of recommendations to print.
 * @return An array of recommended users.
 */
char** user_recommender_iterator(void* void_to_array_string, int num_to_print);

/**
 * @brief Generates user recommendations based on the input query.
 *
 * This function processes the input query to generate user recommendations from the database.
 * It verifies if the user exists, retrieves recommendations, and formats them into a buffer.
 *
 * @param db Pointer to the database.
 * @param query_input The input query string.
 * @return A buffer containing the recommendations, or a newline character if the user does not exist.
 */
int query_user_recommender_original(void** to_fill, DataBase* db, char* query_input);

/**
 * @brief Recommends items to a user based on their preferences.
 *
 * This function generates recommendations for a user by analyzing the provided
 * database and query input. The recommendations are stored in the provided
 * output parameter.
 *
 * @param to_fill A pointer to the output parameter where the recommendations will be stored.
 * @param db A pointer to the database containing user and item information.
 * @param query_input A string containing the query input for generating recommendations.
 * @return An integer indicating the success or failure of the recommendation process.
 */
int query_user_recommender_self(void** to_fill, DataBase* db, char* query_input);

#endif