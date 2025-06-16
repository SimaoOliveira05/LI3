#ifndef OUR_RECOMMENDER_H
#define OUR_RECOMMENDER_H


#include "./data/catalogs/catalogs_utils/our_recommender.h"
#include "./data/elements/user.h"

/**
 * @brief Struct inside every user element that contains the lists of genres, countries and musics listened by the user.
 * 
 */
typedef struct userRecommender UserRecommender;


typedef struct user User;

typedef struct recommenderInfo RecommenderInfo;

typedef struct dotProduct DotProduct;


/**
 * @brief Initializes a UserRecommender structure.
 * @return Pointer to a newly allocated UserRecommender.
 */
UserRecommender* initialize_user_recommender();

/**
 * @brief Frees a UserRecommender structure.
 * @param recommender Pointer to the UserRecommender to be freed.
 */
void free_user_recommender(UserRecommender *recommender);

/**
 * @brief Adds genre listening time to a user's recommender.
 * @param user Pointer to the user.
 * @param genre Genre name.
 * @param listeningTime Listening time to be added.
 */
void add_to_user_genre_recommender(User* user, char* genre, int listeningTime);


/**
 * @brief Adds country listening time to a user's recommender.
 * @param user Pointer to the user.
 * @param country Country name.
 * @param listeningTime Listening time to be added.
 */
void add_to_user_country_recommender(User* user, char* country, int listeningTime);

/**
 * @brief Adds music listening time to a user's recommender.
 * @param user Pointer to the user.
 * @param music_id Music ID.
 * @param listeningTime Listening time to be added.
 */
void add_to_user_music_recommender(User* user, int music_id, int listeningTime);


/**
 * @brief Calculates the dot product for a user and adds it to the dot product list.
 * @param key Key (unused).
 * @param value Pointer to the user.
 * @param user_data Pointer to the RecommenderInfo structure.
 */
void calculate_dot_product(gpointer key, gpointer value, gpointer user_data);


RecommenderInfo* initialize_recommenderInfo(UserRecommender* main_user, int main_user_id, int user_count);

void free_recommenderInfo(RecommenderInfo* recommenderInfo);

/**
 * @brief Transforms the dot product list into a string array.
 * @param recommenderInfo Pointer to the RecommenderInfo structure.
 * @param real_user_count Pointer to store the real number of users.
 * @return Array of user ID strings.
 */
char** transform_into_string_array(RecommenderInfo* recommenderInfo, int* real_user_count);



#endif