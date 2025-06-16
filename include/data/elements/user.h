#ifndef USER_H
#define USER_H

#include <glib.h>
#include "./data/catalogs/catalogs_utils/our_recommender.h"


/**
 * @brief Enum that stores the possible subscription types.
 */ 
typedef enum subscriptionType SubscriptionType;

/**
 * @brief Struct that stores all the information about a user.
 */
typedef struct user User;

/**
 * @brief Creates a user object.
 * 
 * @param username The user's username.
 * @param email The user's email.
 * @param first_name The user's first name.
 * @param last_name The user's last name.
 * @param birth_date The user's birth date.
 * @param country The user's country.
 * @param subscription_type The user's subscription type.
 * @param liked_music_id The IDs of the liked music tracks.
 * @return User* A pointer to the created user object.
 */
User* create_user(char* username, char* email, char* first_name, char* last_name, char* birth_date, char* country, char* subscription_type, GArray* liked_music_id);

UserRecommender* get_user_recommender(User* user);

/**
 * @brief Initializes an empty user object.
 * 
 * @return User* An empty user object.
 */
User* initialize_user();

/**
 * @brief Frees the memory allocated for the user object.
 * 
 * @param user The user object to be freed.
 */
void free_user(User* user);

/**
 * @brief Gets the user's username.
 * 
 * @param user The user object.
 * @return char* The user's username.
 */
int get_user_username(User* user);

/**
 * @brief Sets the user's username.
 * 
 * @param user The user object.
 * @param username The user's username.
 */
void set_user_username(User* user, int username);

/**
 * @brief Gets the user's email.
 * 
 * @param user The user object.
 * @return char* The user's email.
 */
char* get_user_email(User* user);

/**
 * @brief Sets the user's email.
 * 
 * @param user The user object.
 * @param email The user's email.
 */
void set_user_email(User* user, char* email);

/**
 * @brief Gets the user's first name.
 * 
 * @param user The user object.
 * @return char* The user's first name.
 */
char* get_user_first_name(User* user);

/**
 * @brief Sets the user's first name.
 * 
 * @param user The user object.
 * @param first_name The user's first name.
 */
void set_user_first_name(User* user, char* first_name);

/**
 * @brief Gets the user's last name.
 * 
 * @param user The user object.
 * @return char* The user's last name.
 */
char* get_user_last_name(User* user);

/**
 * @brief Sets the user's last name.
 * 
 * @param user The user object.
 * @param last_name The user's last name.
 */
void set_user_last_name(User* user, char* last_name);

/**
 * @brief Gets the user's birth date.
 * 
 * @param user The user object.
 * @return char* The user's birth date.
 */
char* get_user_birth_date(User* user);

/**
 * @brief Sets the user's birth date.
 * 
 * @param user The user object.
 * @param birth_date The user's birth date.
 */
void set_user_birth_date(User* user, char* birth_date);

/**
 * @brief Gets the user's country.
 * 
 * @param user The user object.
 * @return char* The user's country.
 */
char* get_user_country(User* user);

/**
 * @brief Sets the user's country.
 * 
 * @param user The user object.
 * @param country The user's country.
 */
void set_user_country(User* user, char* country);

/**
 * @brief Gets the user's subscription type.
 * 
 * @param user The user object.
 * @return SubscriptionType The user's subscription type.
 */
SubscriptionType get_user_subscription_type(User* user);

/**
 * @brief Sets the user's subscription type.
 * 
 * @param user The user object.
 * @param subscription_type The user's subscription type.
 */
void set_user_subscription_type(User* user, SubscriptionType subscription_type);

/**
 * @brief Gets the IDs of the liked music tracks.
 * 
 * @param user The user object.
 * @return GPtrArray* The liked music IDs.
 */
GArray* get_user_liked_music_id(User* user);

/**
 * @brief Gets the size of the liked music list.
 * 
 * @param user The user object.
 * @return int The size of the liked music list.
 */
int get_user_liked_music_size(User* user);

/**
 * @brief Sets the IDs of the liked music tracks.
 * 
 * @param user The user object.
 * @param liked_music_id The liked music IDs.
 */
void set_user_liked_music_id(User* user, GArray* liked_music_id);


#endif // USER_H