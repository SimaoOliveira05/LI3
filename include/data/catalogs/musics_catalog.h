#ifndef MUSIC_CATALOG_H
#define MUSIC_CATALOG_H

#include "./data/elements/music.h"
#include "./catalogs_utils/liked_musics_list.h"


/**
 * @brief Struct that stores all the information about the music catalog.
 */
typedef struct musicsCatalog MusicsCatalog;

/**
 * @brief Creates a new music catalog with all the data structures initialized.
 * 
 * @return MusicsCatalog* A pointer to the newly created empty catalog.
 */
MusicsCatalog* create_music_catalog();

/**
 * @brief Frees the memory allocated for the catalog and all the data structures inside.
 * 
 * @param catalog The catalog to be freed.
 */
void free_musics_catalog(MusicsCatalog* catalog);

/**
 * @brief Inserts a music into the music hash table.
 * 
 * @param catalog The music catalog.
 * @param music The music to be inserted.
 */
void insert_to_musics_catalog(MusicsCatalog* catalog, Music* music);

/**
 * @brief Retrieves the music object by ID.
 * 
 * @param catalog The music catalog.
 * @param id The ID of the desired music.
 * 
 * @return Music* A pointer to the desired music object.
 */
Music* get_music_by_id(MusicsCatalog* catalog, int id);

/**
 * @brief Inserts a new genre into the genres hash table.
 * 
 * @param catalog The music catalog.
 * @param genre The genre to be inserted.
 */

void insert_to_genres_music_catalog(MusicsCatalog* catalog, char* genre);

/**
 * @brief Retrieves the liked musics list of a genre.
 * 
 * @param catalog The music catalog.
 * @param genre The genre to search.
 * 
 * @return LikedMusicsList* A pointer to the liked musics list of the genre.
 */
LikedMusicsList* get_genre_liked_musics_list(MusicsCatalog* catalog, char* genre);

/**
 * @brief Retrieves the number of existing genres.
 * 
 * @param catalog The music catalog.
 * 
 * @return int The number of existing genres.
 */
int get_number_of_genres(MusicsCatalog* catalog);

/**
 * @brief Searches for a genre in the genres hash table.
 * 
 * @param catalog The music catalog.
 * @param genre The genre to search.
 * 
 * @return int 1 if the genre is found, 0 if not.
 */
int search_on_genres_music_catalog(MusicsCatalog* catalog, char* genre);

/**
 * @brief Updates the liked musics list of a genre.
 * 
 * @param catalog The music catalog.
 * @param genre The genre to update.
 * @param age The age group to update.
 */
void update_genres_music_catalog(MusicsCatalog* catalog, char* genre, int age);

/**
 * @brief Checks if a user is valid by verifying if all the musics they like are valid.
 * 
 * @param musics_ids A list of all the liked musics.
 * @param catalog The music catalog.
 * @return int 0 if the user is valid, 1 if not.
 */
int valid_musics(GArray* musics_ids, MusicsCatalog* catalog);

/**
 * @brief Get the number of likes of a genre by a specific age group.
 * 
 * @param liked_musics_list The list of liked musics of the genre.
 * @param min_age The minimum age of the age group.
 * @param max_age The maximum age of the age group.
 * 
 * @return char* A string containing the genres and the number of likes.
 */

typedef struct genreLikes GenreLikes;

char* genre_likes_get_genre(GenreLikes* genre_likes);
int genre_likes_get_likes(GenreLikes* genre_likes);
GenreLikes* genre_likes_get_element(GenreLikes* array, int index);

void free_genre_like_array(GenreLikes* genre_like_array, int num_of_elems);

GenreLikes* genre_by_age_group(MusicsCatalog* catalog, int min_age, int max_age);

void verify_or_add_genre(MusicsCatalog* catalog, char* genre);

int get_genres_count(MusicsCatalog* catalog);

char* get_music_genre_by_id(MusicsCatalog* catalog, int id);

#endif // MUSICS_CATALOG_H