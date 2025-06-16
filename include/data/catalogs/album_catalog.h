#ifndef ALBUM_CATALOG_H
#define ALBUM_CATALOG_H

#include "./data/elements/album.h"

/**
 * @brief Manager for all the data structures related to the albums.
 * 
 */
typedef struct albumCatalog AlbumCatalog;

/**
 * @brief Creates a album catalog object
 * 
 * @return AlbumCatalog* the album catalog object
 */
AlbumCatalog* create_album_catalog();

/**
 * @brief Frees the memory allocated for the catalog and all the data structures inside.
 * 
 * @param catalog The catalog to be freed.
 */
void free_album_catalog(AlbumCatalog* catalog);

/**
 * @brief Inserts an album into the album hash table (id as key).
 * 
 * @param catalog The album catalog.
 * @param album The album to be inserted.
 */
void insert_to_album_catalog(AlbumCatalog* catalog, Album* album);

/**
 * @brief Retrieves the album object by ID.
 * 
 * @param catalog The album catalog.
 * @param id The ID of the desired album.
 * @return Album* A pointer to the desired album object.
 */
Album* get_album_by_id(AlbumCatalog* catalog, int id);

/**
 * @brief Retrieves the albums object hash table.
 * 
 * @param catalog The album catalog.
 * @return GHashTable* A pointer to the album object hash table.
 */
GHashTable* get_albums(AlbumCatalog* catalog);


#endif // ALBUM_CATALOG_H