#ifndef ARTIST_DISCOGRAPHY_H
#define ARTIST_DISCOGRAPHY_H

#include <glib.h>

/**
 * @brief Auxiliar struct for query 2, only stores relevant information for the query
 * 
 */
typedef struct artist_discography ArtistDiscography;

/**
 * @brief Creates an ArtistDiscography object.
 * 
 * @param id The ID of the artist.
 * @param name The name of the artist.
 * @param type The type of the artist (0 for individual, 1 for group).
 * @param discography The discography duration in seconds.
 * @param country The country of the artist.
 * @return ArtistDiscography* A pointer to the created ArtistDiscography object.
 */
ArtistDiscography* create_artist_discography(int id, char* name, short int type, int discography, char* country);

/**
 * @brief Initializes an empty object of type ArtistDiscography.
 * 
 * @return ArtistDiscography* A pointer to the initialized empty object.
 */
ArtistDiscography* inicialize_artist_discography();

/**
 * @brief Frees the memory allocated for the ArtistDiscography object.
 * 
 * @param artist_discography The ArtistDiscography object to be freed.
 */
void free_artist_discography(ArtistDiscography* artist_discography);

/**
 * @brief Gets the name of the artist from the ArtistDiscography object.
 * 
 * @param artist The ArtistDiscography object.
 * @return char* The name of the artist.
 */
char* get_artist_discography_name(ArtistDiscography* artist);

/**
 * @brief Gets the country of the artist from the ArtistDiscography object.
 * 
 * @param artist The ArtistDiscography object.
 * @return char* The country of the artist.
 */
char* get_artist_discography_country(ArtistDiscography* artist);

/**
 * @brief Gets the discography duration of the artist from the ArtistDiscography object.
 * 
 * @param artist The ArtistDiscography object.
 * @return int The discography duration in seconds.
 */
int get_artist_discography_discography(ArtistDiscography* artist);

/**
 * @brief Gets the type of the artist from the ArtistDiscography object.
 * 
 * @param artist The ArtistDiscography object.
 * @return int 0 if individual, 1 if group.
 */
int get_artist_discography_type(ArtistDiscography* artist);

/**
 * @brief Compares two ArtistDiscography objects by their discography duration in descending order.
 * 
 * @param a The first ArtistDiscography object.
 * @param b The second ArtistDiscography object.
 * @return int 1 if the first object has a greater discography duration, -1 if the second object has a greater discography duration, 0 if they are equal.
 */
gint compare_artist_discography_desc(const void* a, const void* b);

#endif // ARTIST_DISCOGRAPHY_H