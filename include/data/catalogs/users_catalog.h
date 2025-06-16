#ifndef USERS_CATALOG_H
#define USERS_CATALOG_H

#include "./data/elements/user.h"
#include "./utils/validations.h"
#include "./data/catalogs/catalogs_utils/recommender.h"



/**
 * @brief Manages all data structures related to users.
 */
typedef struct usersCatalog UsersCatalog;

/**
 * @brief Creates a user catalog object with all data structures initialized.
 * 
 * @return UsersCatalog* An empty catalog.
 */
UsersCatalog* create_users_catalog();

/**
 * @brief Frees the memory allocated for the catalog and all its data structures.
 * 
 * @param catalog The catalog to be freed.
 */
void free_users_catalog(UsersCatalog* catalog);

/**
 * @brief Inserts a user into the user hash table.
 * 
 * @param catalog The user catalog.
 * @param user The user to be inserted.
 */
void insert_to_users_catalog(UsersCatalog* catalog, User* user);

/**
 * @brief Retrieves a user object by ID from the user hash table.
 * 
 * @param catalog The user catalog.
 * @param id The ID of the desired user.
 * @return User* The desired user object.
 */
User* get_user_by_id(UsersCatalog* catalog, int id);

/**
 * @brief Retrieves the user object hash table.
 * 
 * @param catalog The user catalog.
 * @return GHashTable* The user object hash table.
 */
GHashTable* get_users (UsersCatalog* catalog);

/**
 * @brief Get the catalog recommender object
 * 
 * @param catalog users catalog
 * @return recommender* the recommender object
 */
Recommender* get_catalog_recommender(UsersCatalog* catalog);

/**
 * @brief Set the recommender object
 * 
 * @param catalog users catalog
 * @param recommender recommender object
 */
void set_recommender(UsersCatalog *catalog, Recommender* recommender);

#endif // USERS_CATALOG_H