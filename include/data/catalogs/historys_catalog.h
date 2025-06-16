#ifndef HISTORYS_CATALOG_H
#define HISTORYS_CATALOG_H

#include "./data/elements/history.h"
#include <glib.h>


/**
 * @brief Manager for all the data structures related to the historys.
 * 
 */
typedef struct historysCatalog HistorysCatalog;

/**
 * @brief Creates a historys catalog object
 * 
 * @return HistorysCatalog* the historys catalog object
 */
HistorysCatalog* create_historys_catalog();

/**
 * @brief Frees the memory allocated for the catalog and all the data structures inside.
 * 
 * @param catalog The catalog to be freed.
 */
void free_historys_catalog(HistorysCatalog* catalog);

/**
 * @brief Inserts an history into both history tables.
 * 
 * The catalog contains 2 hash tables one has user id as key and the other has the history year as key.
 * 
 * @param catalog The history catalog.
 * @param history The history to be inserted.
 */
void insert_to_historys_catalog(HistorysCatalog* catalog, History* history);

/**
 * @brief Retrieves all the history objects from a specific user.
 * 
 * @param catalog The history catalog.
 * @param user_id The user id of the desired historys.
 * @return GPtrArray* A pointer to the array of history objects.
 */
GPtrArray* get_history_list_by_user(HistorysCatalog* catalog, int user_id);


/**
 * @brief Retrieves the history objects hash table by user.
 * 
 * @param catalog The history catalog.
 * @return GHashTable* A pointer to the history objects hash table.
 */
GHashTable* get_historybyuser(HistorysCatalog* catalog);

/**
 * @brief Inserts a user into the historys hash table where keys are user ids.
 * 
 * @param catalog The history catalog.
 * @param user_id The user id to be inserted.
 */
void insert_user_to_history_table(HistorysCatalog* catalog, int user_id);

/**
 * @brief Verifies if a user exists in the historys catalog.
 * 
 * @param catalog The history catalog.
 * @param user_id The user id to be verified.
 * @return int 1 if the user exists, 0 otherwise.
 */
int verify_if_user_exists(HistorysCatalog* catalog, int user_id);

/**
 * @brief Function that calculates the top 10 artists per week after having stored all the information about the auditions for each artist.
 * 
 * @param catalog The historys catalog.
 */
void calculate_top_10_per_week(HistorysCatalog* catalog);

/**
 * @brief Manage an artist and its audition duration on the artistTree of a specific week.
 * 
 * @param catalog The historys catalog.
 * @param week_offset The week offset.
 * @param artist_id The artist id.
 * @param duration The duration.
 */
void actualize_artistDurationTree(HistorysCatalog* catalog, int week_offset, int artist_id, int duration);

/**
 * @brief Gives the top 10 artists of a specific week.
 * 
 * @param catalog The historys catalog.
 * @param week_offset The week offset.
 * 
 * @return int* The top 10 artists.
 */
int* get_top_10_by_week(HistorysCatalog* catalog, int week_offset);

/**
 * @brief Gets the minimum and maximum week offset that exists in the historys catalog.
 * 
 * @param catalog The historys catalog.
 * @param min_week_offset The minimum week offset.
 * @param max_week_offset The maximum week offset.
 */
void get_min_and_max_week_offset(HistorysCatalog* catalog, int* min_week_offset, int* max_week_offset);

#endif