#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include <glib.h>


typedef struct recommender Recommender; 

/**
 * @brief Creates a matrix where lines are user ids and columns are genre names that contains the number of likes of each user for each genre
 * 
 * @param userSize The total number of users
 * @param genreSize The total number of genres
 * @return Recommender* Recommender object with the matrix initialized
 */
Recommender* create_recommender(int userSize, int genreSize);

/**
 * @brief Frees the memory allocated for the Recommender object
 * 
 * @param recommender The Recommender object to be freed
 */
void free_recommender(Recommender* recommender);

/**
 * @brief Adds a user to the recommender matrix. The user is added to the last line of the matrix
 * 
 * @param recommender The recommender struct containing the matrix
 * @param id The user to be added
 */
void add_user_to_recommender(Recommender* recommender, char* id);

/**
 * @brief Adds a genre to the recommender matrix or increments the likes. The genre is added to the last column of the matrix
 * 
 * @param recommender The recommender struct containing the matrix
 * @param genre The genre to be added or incremented
 */
void add_like_to_recommender(Recommender* recommender, char* genre);

/**
 * @brief Increments the user count of the recommender struct
 * 
 * @param recommender The recommender struct to be incremented
 */
void increment_user_count(Recommender* recommender);

/**
 * @brief Get the matrix of the recommender struct
 * 
 * @param recommender The recommender struct
 * @return int** Matrix where lines are user ids and columns are genre names that contains the number of likes of each user for each genre
 */
int **get_recommender_matrix(Recommender* recommender
);

/**
 * @brief Get the user ids of the recommender struct
 * 
 * @param recommender The recommender struct
 * @return char** Array of user ids
 */
char **get_recommender_user_ids(Recommender* recommender);

/**
 * @brief Get the genre names of the recommender struct
 * 
 * @param recommender The recommender struct
 * @return char** Array of genre names
 */
char **get_recommender_genre_names(Recommender* recommender);

/**
 * @brief Get the number of users of the recommender struct
 * 
 * @param recommender The recommender struct
 * @return int Number of users
 */
int get_recommender_num_users(Recommender* recommender);

/**
 * @brief Get the number of genres of the recommender struct
 * 
 * @param recommender The recommender struct
 * @return int Number of genres
 */
int get_recommender_num_genres(Recommender* recommender);

#endif // RECOMMENDER_H