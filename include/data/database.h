#ifndef DATABASE_H
#define DATABASE_H

#include "./data/catalogs/users_catalog.h"
#include "./data/catalogs/artists_catalog.h"
#include "./data/catalogs/musics_catalog.h"
#include "./data/catalogs/historys_catalog.h"
#include "./data/catalogs/album_catalog.h"
#include "./data/catalogs/catalogs_utils/recommender.h"


/**
 * @brief Database contains all the catalogs.
 * 
 */
typedef struct database DataBase;

/**
 * @brief Initializes the database with empty catalogs.
 * 
 * @return DataBase* The initialized database.
 */
DataBase* initialize_database();

/**
 * @brief Frees the memory allocated for the database.
 * 
 * @param database The database to be freed.
 */
void free_database(DataBase* database);

/**
 * @brief Populates the database with the data from the files.
 * 
 * @param database The database to be populated.
 * @param path_to The path to the files.
 * @param test 1 if it is in test mode, 0 otherwise.
 * @return int 1 if the database was populated successfully, 0 otherwise.
 */
int populate_database(DataBase* database, char* path_to, int test);

/**
 * @brief Gets the users catalog.
 * 
 * @param database The database.
 * @return UsersCatalog* The users catalog.
 */
UsersCatalog* get_users_catalog(DataBase* database);

/**
 * @brief Gets the artists catalog.
 * 
 * @param database The database.
 * @return ArtistsCatalog* The artists catalog.
 */
ArtistsCatalog* get_artists_catalog(DataBase* database);

/**
 * @brief Gets the musics catalog.
 * 
 * @param database The database.
 * @return MusicsCatalog* The musics catalog.
 */
MusicsCatalog* get_musics_catalog(DataBase* database);

/**
 * @brief Retrieves the history catalog from the given database.
 *
 * @param database A pointer to the DataBase structure from which the history catalog is to be retrieved.
 * @return A pointer to the HistorysCatalog structure.
 */
HistorysCatalog* get_historys_catalog(DataBase* database);



/**
 * @brief Gets the albums catalog.
 * 
 * @param database The database.
 * @return AlbumCatalog* The albums catalog.
 */
AlbumCatalog* get_albums_catalog(DataBase* database);

/**
 * @brief Gets the recommender system.
 * 
 * @param database The database.
 * @return Recommender* The recommender system.
 */
Recommender* get_recommender(DataBase* database);

/**
 * @brief Creates and populates a Recommender instance.
 *
 * This function initializes a Recommender instance and populates it with data
 * from the provided HistorysCatalog and DataBase. The number of users and genres
 * to be considered are specified by the parameters nUsers and nGenres respectively.
 *
 * @param historyCatalog Pointer to the HistorysCatalog containing user history data.
 * @param nUsers The number of users to be considered for the recommender.
 * @param nGenres The number of genres to be considered for the recommender.
 * @param database Pointer to the DataBase containing additional data.
 * @return Pointer to the newly created and populated Recommender instance.
 */
Recommender* create_and_populate_recommender(HistorysCatalog* historyCatalog,int nUsers, int nGenres,DataBase* database);
#endif