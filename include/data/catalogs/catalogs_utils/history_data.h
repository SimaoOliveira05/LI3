#ifndef HISTORY_DATA_H
#define HISTORY_DATA_H

#include <glib.h>
#include "./data/elements/history.h"
#include "./data/catalogs/musics_catalog.h"
#include "./utils/day_conversion.h"
#include "./utils/strsep_by_token.h"
#include "./data/elements/music.h"
#include "./data/database.h"

/**
 * @brief Struct containing all the relevant information about the user's listening history.
 * 
 */
typedef struct HistoryData HistoryData;

/**
 * @brief Auxiliar struct to store information related to an artist.
 * 
 */
typedef struct ArtistTime ArtistTime;

/**
 * @brief Frees all the memory allocated for the history data structure.
 * 
 * @param historyData The history data structure to be freed.
 * @param nArtists The size of the top n artists array.
 */
void free_historyData(HistoryData* historyData,int nArtists);

/**
 * @brief Builds the history data structure that contains all relevant information about the user's listening history.
 * 
 * @param historyList All the user's listening history.
 * @param database The database.
 * @param nArtists Top n artists that the user listened to.
 * @param year What year to consider.
 * @return HistoryData* The history data structure.
 */
HistoryData* build_history_data(GPtrArray* historyList, DataBase* database, int nArtists,char* year);

/**
 * @brief Get the total listening time of the user in a specific year.
 * 
 * @param data History data.
 * @return char* listening time in the format "HH:MM:SS".
 */
char* get_listening_time(HistoryData* data);

/**
 * @brief Get the total number of musics listened by the user in a specific year.
 * 
 * @param data History data.
 * @return int total number of musics listened.
 */
int get_music_count(HistoryData* data);

/**
 * @brief Get the most listened genre by the user in a specific year.
 * 
 * @param data History data.
 * @return char* The most listened genre.
 */
char* get_most_listened_genre(HistoryData* data);

/**
 * @brief Get the top n artist listened by a user in a specific year.
 * 
 * 0 being the most linstend artist.
 * 
 * @param data History data.
 * @param index The index of the artist.
 * @return char* The n most listened artist.
 */
char* get_artist_id_by_index(HistoryData* data, int index);

/**
 * @brief Get the top n artist listening time by a user in a specific year.
 * 
 * 0 being the most linstend artist.
 * 
 * @param data History data.
 * @param index The index of the artist.
 * @return char* The listening time of the artist in the format "HH:MM:SS".
 */
char* get_artist_time_by_index(HistoryData* data, int index);

int get_artist_time_by_index_int(HistoryData* data, int index);

/**
 * @brief Get the top n artist musics heard by a user in a specific year.
 * 
 * 0 being the most linstend artist.
 * 
 * @param data History data.
 * @param index The index of the artist.
 * @return int The number of musics of the artist heard by the user.
 */
int get_artist_music_count_by_index(HistoryData* data, int index);

/**
 * @brief Get the most heard album by the user in a specific year.
 * 
 * @param data History data.
 * @return char* The most heard album ID.
 */
char* get_most_heard_album(HistoryData* data);

/**
 * @brief Get the most listened hour by the user in a specific year.
 * 
 * @param data History data.
 * @return int The most listened hour.
 */
int get_most_listened_hour(HistoryData* data);

/**
 * @brief Get the most listened date by the user in a specific year.
 * 
 * Fills the month and day pointers with the most listened date.
 * 
 * @param data History data.
 * @param month month to be filled
 * @param day day to be filled.
 */
void get_most_listened_date(HistoryData* data, int* month, int* day);

#endif