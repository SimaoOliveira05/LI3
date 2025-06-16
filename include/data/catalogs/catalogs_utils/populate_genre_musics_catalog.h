#ifndef POPULATE_GENRE_CATALOG_H
#define POPULATE_GENRE_CATALOG_H

#include "./data/database.h"

/**
 * @brief Populates the genre musics catalog with the data from the database.
 * 
 * @param db The database.
 */
void populate_genre_musics_catalog(DataBase* db);

#endif // POPULATE_GENRE_CATALOG_H