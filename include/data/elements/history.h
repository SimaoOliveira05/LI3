#ifndef HISTORY_H
#define HISTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Opaque structure representing a history entry.
 */
typedef struct history History;

/**
 * @brief Creates a new history entry.
 * 
 * @param user_id Identifier for the user.
 * @param music_id Identifier for the music.
 * @param date Date of the history entry in the format YYYY-MM-DD.
 * @param time Time of the history entry in the format HH:MM:SS.
 * @param duration Duration of the history entry in seconds.
 * @param platform Platform identifier as a string ("mobile" or "desktop").
 * @return Pointer to the newly created History structure.
 */
History* create_history(char* user_id, char* music_id, char* date, char* time, int duration, char* platform);

/**
 * @brief Initializes a new history entry.
 * 
 * @return Pointer to the newly initialized History structure.
 */
History* initialize_history();

/**
 * @brief Frees the memory allocated for a history entry.
 * 
 * @param history Pointer to the History structure to be freed.
 */
void free_history(History* history);

/**
 * @brief Gets the user identifier of the history entry.
 * 
 * @param history Pointer to the History structure.
 * @return The user identifier of the history entry.
 */
int get_history_user_id(History* history);

/**
 * @brief Sets the user identifier of the history entry.
 * 
 * @param history Pointer to the History structure.
 * @param user_id The user identifier to set.
 */
void set_history_user_id(History* history, int user_id);

/**
 * @brief Gets the music identifier of the history entry.
 * 
 * @param history Pointer to the History structure.
 * @return The music identifier of the history entry.
 */
int get_history_music_id(History* history);

/**
 * @brief Sets the music identifier of the history entry.
 * 
 * @param history Pointer to the History structure.
 * @param music_id The music identifier to set.
 */
void set_history_music_id(History* history, int music_id);

/**
 * @brief Gets the time of the history entry.
 * 
 * @param history Pointer to the History structure.
 * @return A newly allocated string representing the time in the format HH:MM:SS. The caller is responsible for freeing the memory.
 */
char* get_history_time(History* history);

/**
 * @brief Gets the date of the history entry.
 * 
 * @param history Pointer to the History structure.
 * @return A newly allocated string representing the date in the format YYYY-MM-DD. The caller is responsible for freeing the memory.
 */
char* get_history_date(History* history);

/**
 * @brief Gets the duration of the history entry.
 * 
 * @param history Pointer to the History structure.
 * @return The duration of the history entry in seconds.
 */
int get_history_duration(History* history);

/**
 * @brief Sets the duration of the history entry.
 * 
 * @param history Pointer to the History structure.
 * @param duration Duration of the history entry in seconds.
 */
void set_history_duration(History* history, int duration);

/**
 * @brief Gets the platform of the history entry.
 * 
 * @param history Pointer to the History structure.
 * @return The platform identifier.
 */
int get_history_platform(History* history);

/**
 * @brief Sets the platform of the history entry.
 * 
 * @param history Pointer to the History structure.
 * @param platform Platform identifier as a string.
 */
void set_history_platform(History* history, char* platform);

#endif // HISTORY_H