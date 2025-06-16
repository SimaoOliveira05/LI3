#ifndef ARTIST_CATALOG_H
#define ARTIST_CATALOG_H

#include "./data/elements/artist.h"
#include "./data/catalogs/catalogs_utils/artist_discography.h"
#include <string.h>
#include <stdio.h>
#include <glib.h>

/**
 * @brief Manager for all the data structures related to the artists.
 */
typedef struct artistsCatalog ArtistsCatalog;

/**
 * @brief Creates an artist catalog with all the data structures initialized.
 * 
 * @return ArtistsCatalog* A pointer to the newly created empty catalog.
 */
ArtistsCatalog* create_artist_catalog();

/**
 * @brief Frees the memory allocated for the catalog and all the data structures inside.
 * 
 * @param catalog The catalog to be freed.
 */
void free_artists_catalog(ArtistsCatalog* catalog);

/**
 * @brief Inserts an artist into the artist hash table.
 * 
 * @param catalog The artist catalog.
 * @param artist The artist to be inserted.
 */
void insert_to_artists_catalog(ArtistsCatalog* catalog, Artist* artist);

/**
 * @brief Retrieves the artist object by ID.
 * 
 * @param catalog The artist catalog.
 * @param id The ID of the desired artist.
 * @return Artist* A pointer to the desired artist object.
 */
Artist* get_artist_by_id(ArtistsCatalog* catalog, int id);

/**
 * @brief Retrieves the artists object hash table.
 * 
 * @param catalog The artist catalog.
 * @return GHashTable* A pointer to the artist object hash table.
 */
GHashTable* get_artists(ArtistsCatalog* catalog);


/**
 * @brief Formats the artist discography into a string.
 * 
 * This function takes an artist catalog, the number of artists to include, and an optional country filter.
 * It formats the artist discography into a string, including the artist's name, subscription type, discography,
 * and country. If the country is specified, only artists from that country are included.
 * 
 * @param catalog The artist catalog.
 * @param n_artists The number of artists to include.
 * @param country The country filter (optional).
 * @return char* The formatted artist discography string.
 */
ArtistDiscography** top_N_artists(ArtistsCatalog* catalog, char* n_artists, char* country);

/**
 * @brief Sorts the array of artist discographies by discography duration. (Descreasing order)
 * 
 * @param catalog Artist Catalog
 */
void transform_into_sorted_discography_array (ArtistsCatalog* catalog);

/**
 * @brief Checks if a music is valid by checking if the artist ID of the respective constituent is in the artist catalog.
 * 
 * @param artist_ids List of artist IDs.
 * @param catalog Artist catalog
 * @return int 0 if the music is not valid, 1 otherwise.
 */
int valid_artist(GArray *artist_ids, ArtistsCatalog* catalog);

/**
 * @brief Adds the duration of a music to the respective artirts that created it.
 * 
 * @param artist_ids IDs of the artists that created the music.
 * @param catalog Artist catalog.
 * @param duration Music DUration.
 */
void add_music_duration_to_artist_list (GArray* artist_ids, ArtistsCatalog* catalog, int duration);

/**
 * @brief Get the artist dicography array object
 * 
 * @param catalog Artist Catalog
 * @return GPtrArray* Aritst discography object array.
 */
GPtrArray* get_artist_dicography_array(ArtistsCatalog* catalog);

/**
 * @brief Calculates the recipe of an artist.
 * 
 * @param catalog Artist catalog.
 * @param artist Artist object.
 */
float calculate_recipe(ArtistsCatalog* catalog, Artist* artist);

/**
 * @brief Actualizes the groups array where the artist is part of.
 * 
 * @param catalog Artist catalog.
 */
void actualize_artist_group_participation(ArtistsCatalog* catalog);

#endif // ARTIST_CATALOG_H