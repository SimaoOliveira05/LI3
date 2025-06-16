#ifndef MUSIC_H
#define MUSIC_H

#include <glib.h>

/**
 * @brief Struct that stores all the information about a music track.
 */
typedef struct music Music;

/**
 * @brief Creates a music object.
 * 
 * @param id The music's ID.
 * @param artist_id The IDs of the artists.
 * @param duration The duration of the music.
 * @param year The release year of the music.
 * @param title The title of the music.
 * @param genre The genre of the music.
 * @return Music* A pointer to the created music object.
 */
Music* create_music(char* id, GArray* artist_id, char* duration, char* album_id, char* year,
                    char* title, char* genre);

/**
 * @brief Initializes an empty music object.
 * 
 * @return Music* An empty music object.
 */
Music* initialize_music();

/**
 * @brief Frees the memory allocated for the music object.
 * 
 * @param music The music object to be freed.
 */
void free_music(Music* music);

/**
 * @brief Gets the music's ID.
 * 
 * @param music The music object.
 * @return char* The music's ID.
 */
int get_music_id(Music* music);

/**
 * @brief Sets the music's ID.
 * 
 * @param music The music object.
 * @param id The music's ID.
 */
void set_music_id(Music* music, int id);

/**
 * @brief Gets the IDs of the artists.
 * 
 * @param music The music object.
 * @return GPtrArray* The artist IDs.
 */
GArray* get_music_artist_id(Music* music);

/**
 * @brief Sets the IDs of the artists.
 * 
 * @param music The music object.
 * @param artist_id The artist IDs.
 */
void set_music_artist_id(Music* music, GArray* artist_id);

/**
 * @brief Gets the duration of the music.
 * 
 * @param music The music object.
 * @return int The duration of the music.
 */
int get_music_duration(Music* music);

/**
 * @brief Sets the duration of the music.
 * 
 * @param music The music object.
 * @param time The duration of the music.
 */
void set_music_duration(Music* music, int time);

/**
 * @brief Gets the release year of the music.
 * 
 * @param music The music object.
 * @return short unsigned int The release year of the music.
 */
short unsigned int get_music_year(Music* music);

/**
 * @brief Sets the release year of the music.
 * 
 * @param music The music object.
 * @param year The release year of the music.
 */
void set_music_year(Music* music, short unsigned int year);

/**
 * @brief Gets the title of the music.
 * 
 * @param music The music object.
 * @return char* The title of the music.
 */
char* get_music_title(Music* music);

/**
 * @brief Sets the title of the music.
 * 
 * @param music The music object.
 * @param title The title of the music.
 */
void set_music_title(Music* music, char* title);

/**
 * @brief Gets the genre of the music.
 * 
 * @param music The music object.
 * @return char* The genre of the music.
 */
char* get_music_genre(Music* music);

/**
 * @brief Sets the genre of the music.
 * 
 * @param music The music object.
 * @param genre The genre of the music.
 */
void set_music_genre(Music* music, char* genre);

/**
 * @brief Gets the number of artists that participated in the music.
 * 
 * @param music The music object.
 * 
 * @return int The number of artists.
 */
int get_number_of_artists(Music* music);

/**
 * @brief Get the album id of the music object.
 * 
 * @param music The music object.
 * @return int Album id
 */
int get_music_album_id(Music* music);

#endif // MUSIC_H