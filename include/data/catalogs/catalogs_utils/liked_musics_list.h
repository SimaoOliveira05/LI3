#ifndef LIKED_MUSICS_LIST_H
#define LIKED_MUSICS_LIST_H

#include <glib.h>

/**
 * @brief Struct that stores a list of accumulated likes by age group decrescently ordered.
 */
typedef struct likedMusicsList LikedMusicsList;

/**
 * @brief Struct that stores the amount of accumulated likes on a age group.
 */
typedef struct likesByAge LikesByAge;

/**
 * @brief Initializes a new liked musics list.
 * 
 * @return LikedMusicsList* A pointer to the newly created list.
 */
LikedMusicsList* initialize_liked_musics_list();

/**
 * @brief Frees the memory allocated for the liked musics list.
 * 
 * @param list The list to be freed.
 */
void free_liked_musics_list(LikedMusicsList* list);

/**
 * @brief Creates a new likes by age group struct.
 * 
 * @param age The age group.
 * @param likes The amount of likes.
 * 
 * @return LikesByAge* A pointer to the newly created struct.
 */
LikesByAge* create_likes_by_age(int age, int likes);

/**
 * @brief Inserts a new likes by age group struct into the liked musics list.
 * 
 * @param list The list to insert the struct.
 * @param age The age group.
 * @param likes The amount of likes.
 * 
 * @return LikedMusicsList* A pointer to the updated list.
 */
LikedMusicsList* insert_to_liked_musics_list(LikedMusicsList* list, int age);

/**
 * @brief Compares two LikesByAge structs by age.
 * 
 * @param a The first LikesByAge struct.
 * @param b The second LikesByAge struct.
 * 
 * @return gint A positive integer if a > b, a negative integer if a < b, or 0 if a == b.
 */
gint compare_liked_musics_list(gconstpointer a, gconstpointer b);

/**
 * @brief Retrieves the amount of likes by age group.
 * 
 * @param list The list to search.
 * @param age The age group.
 * 
 * @return int The amount of likes on the given age group.
 */
int get_likes_by_age_group(LikedMusicsList* list, int min_age, int max_age);

#endif // LIKED_MUSICS_LIST_H