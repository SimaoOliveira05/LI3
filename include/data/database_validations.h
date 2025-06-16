#ifndef DATABASE_VALIDATIONS_H
#define DATABASE_VALIDATIONS_H

#include "./data/catalogs/musics_catalog.h"
#include "./data/catalogs/artists_catalog.h"
#include "./data/catalogs/album_catalog.h"
#include "./data/catalogs/historys_catalog.h"
#include "./data/catalogs/users_catalog.h"
#include "./utils/validations.h" 
#include "./utils/time.h"
#include "./data/catalogs/catalogs_utils/parse_utils.h"

int add_album(char** tokens, AlbumCatalog* albumsCatalog, ArtistsCatalog* artistsCatalog);

/**
 * @brief Validates an artist, creates it and adds it to the database
 * 
 * @param tokens List of strings containing all artist information
 * @param artistCatalog artist catalog
 * @return int 0 if the artist is valid, 1 otherwise
 */
int validate_and_add_artist(char** tokens,ArtistsCatalog* artistCatalog);

/**
 * @brief Validates a history, creates it and adds it to the database
 * 
 * @param tokens List of strings containing all history information
 * @param artistsCatalog artist catalog to check if the artists in the history are valid
 * @param musicsCatalog music catalog to check if the musics in the history are valid
 * @param historyCatalog history catalog
 * @return int 0 if the history is valid, 1 otherwise
 */
int validate_and_add_history(char** tokens, ArtistsCatalog* artistsCatalog, MusicsCatalog* musicsCatalog, HistorysCatalog* historyCatalog);

/**
 * @brief Validates a music, creates it and adds it to the database
 * 
 * @param tokens List of strings containing all music information
 * @param musicCatalog music catalog
 * @param artistCatalog artist catalog to check if the creators of the song are valid
 * @param albumCatalog album catalog to check if the album of the song is valid
 * @return int 0 if the music is valid, 1 otherwise
 */
int validate_and_add_music(char** tokens, MusicsCatalog* musicCatalog, ArtistsCatalog* artistsCatalog, AlbumCatalog* albumCatalog);

/**
 * @brief Validates a user, creates it and adds it to the database
 * 
 * @param tokens List of strings containing all users information
 * @param usersCatalog users catalog
 * @param msuicsCatalog msuic catalog to check if the liked songs are valid
 * @return int 0 if the user is valid, 1 otherwise
 */
int validate_and_add_user(char** tokens, UsersCatalog* usersCatalog, MusicsCatalog* musicsCatalog, HistorysCatalog* historyCatalog);

/**
 * @brief Validates an entry, creates it and adds it to the database
 * 
 * @param tokens List of strings containing all entry information
 * @param database pointer to the database where the entry will be added
 * @param line the line of data to be validated and added
 * @return int 0 if the entry is valid, 1 otherwise
 */
int validate_and_add (char** tokens, void* database, char* line);

#endif