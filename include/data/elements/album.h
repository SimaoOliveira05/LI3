#ifndef ALBUM_H
#define ALBUM_H

#include <glib.h>

/**
 * @brief Struct that stores all the information about an album
 * 
 */
typedef struct album Album;

/**
 * @brief Creates a new album with the given parameters
 * 
 * @param id The ID of the album
 * @param title The title of the album
 * @param artist_id The array of artist IDs associated with the album
 * @param year The release year of the album
 * @param producers_list The array of producers associated with the album
 * @return Album* Pointer to the newly created album
 */
Album* create_album(char* id, char* title, GArray* artist_id, char* year, GArray* producers_list);

/**
 * @brief Initializes a new album with default values
 * 
 * @return Album* Pointer to the newly initialized album
 */
Album* initialize_album();

/**
 * @brief Frees the memory allocated for an Album structure.
 *
 * This function releases all the resources associated with the given Album
 * structure, including any dynamically allocated memory within the structure.
 *
 * @param album A pointer to the Album structure to be freed.
 */
void free_album(Album* album);

/**
 * @brief Gets the ID of the album
 * 
 * @param album Pointer to the album
 * @return int The ID of the album
 */
int get_album_id(Album* album);

/**
 * @brief Sets the ID of the given album.
 *
 * This function assigns the specified ID to the provided album.
 *
 * @param album A pointer to the Album structure whose ID is to be set.
 * @param id The ID to be assigned to the album.
 */
void set_album_id(Album* album, int id);

/**
 * @brief Gets the title of the album
 * 
 * @param album Pointer to the album
 * @return char* The title of the album
 */
char* get_album_title(Album* album);

/**
 * @brief Sets the title of the given album.
 *
 * This function assigns the specified title to the provided album.
 *
 * @param album A pointer to the Album structure whose title is to be set.
 * @param title The title to be assigned to the album.
 */
void set_album_title(Album* album, char* title);

/**
 * @brief Gets the array of artist IDs associated with the album
 * 
 * @param album Pointer to the album
 * @return GArray* The array of artist IDs
 */
GArray* get_album_artist_id(Album* album);

/**
 * @brief Sets the array of artist IDs associated with the given album.
 *
 * This function assigns the specified array of artist IDs to the provided album.
 *
 * @param album A pointer to the Album structure whose artist IDs are to be set.
 * @param artist_id The array of artist IDs to be assigned to the album.
 */
void set_album_artist_id(Album* album, GArray* artist_id);

/**
 * @brief Gets the release year of the album
 * 
 * @param album Pointer to the album
 * @return char* The release year of the album
 */
char* get_album_year(Album* album);

/**
 * @brief Sets the release year of the given album.
 *
 * This function assigns the specified release year to the provided album.
 *
 * @param album A pointer to the Album structure whose release year is to be set.
 * @param year The release year to be assigned to the album.
 */
void set_album_year(Album* album, char* year);

/**
 * @brief Gets the array of producers associated with the album
 * 
 * @param album Pointer to the album
 * @return GArray* The array of producers
 */
GArray* get_album_producers_list(Album* album);

/**
 * @brief Sets the array of producers associated with the given album.
 *
 * This function assigns the specified array of producers to the provided album.
 *
 * @param album A pointer to the Album structure whose producers are to be set.
 * @param producers_list The array of producers to be assigned to the album.
 */
void set_album_producers_list(Album* album, GArray* producers_list);

#endif // ALBUM_H