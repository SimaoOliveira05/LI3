#ifndef ARTIST_H
#define ARTIST_H

#include <glib.h>

/**
 * @brief Struct that stores all the information about an artist
 * 
 */
typedef struct artist Artist;

/**
 * @brief Create a artist object
 * 
 * @param id id
 * @param name name 
 * @param recipe_per_stream recipe per stream
 * @param id_constituent ids of the constituents
 * @param country country
 * @param type 0 for individual, 1 for group
 * @return Artist* returns a pointer to the created object
 */
Artist* create_artist(char* id, char* name, char* recipe_per_stream, GArray* id_constituent, char* country, char* type);

/**
 * @brief Initializes an empty object of type Artist
 * 
 * @return Artist* empty object
 */
Artist* initialize_artist();

/**
 * @brief Frees the memory allocated for the artist object
 * 
 * @param artist object to be freed
 */
void free_artist(Artist* artist);

/**
 * @brief Get the artist id
 * 
 * @param artist artist object
 * @return char* artist id
 */
int get_artist_id(Artist* artist);

/**
 * @brief Set the artist id
 * 
 * @param artist artist object
 * @param id artist id
 */
void set_artist_id(Artist* artist, int id);

/**
 * @brief Get the artist name
 * 
 * @param artist artist object
 * @return char* artist name
 */
char* get_artist_name(Artist* artist);

/**
 * @brief Set the artist name
 * 
 * @param artist artist object
 * @param name artist name
 */
void set_artist_name(Artist* artist, char* name);

/**
 * @brief Get the artist recipe per stream
 * 
 * @param artist artist object
 * @return int artist recipe per stream
 */
int get_artist_recipe_per_stream(Artist* artist);

/**
 * @brief Set the artist recipe per stream
 * 
 * @param artist artist object
 * @param recipe_per_stream artist recipe per stream
 */
void set_artist_recipe_per_stream(Artist* artist, int recipe_per_stream);

/**
 * @brief Get the artist ids of the constituents (if it is a group)
 * 
 * @param artist artist object
 * @return GPtrArray* artist id constituent
 */
GArray* get_artist_id_constituent(Artist* artist);

/**
 * @brief Set the artist ids of the constituents
 * 
 * @param artist artist object
 * @param id_constituent artist id constituents
 */
void set_artist_id_constituent(Artist* artist, GArray* id_constituent);

/**
 * @brief Get the artist country
 * 
 * @param artist artist object
 * @return char* artist country
 */
char* get_artist_country(Artist* artist);

/**
 * @brief Set the artist country
 * 
 * @param artist artist object
 * @param country artist country
 */
void set_artist_country(Artist* artist, char* country);

/**
 * @brief Get the artist type
 * 
 * @param artist artist object
 * @return 0 if individual, 1 if group
 */
short int get_artist_type(Artist* artist);

/**
 * @brief Set the artist type
 * 
 * @param artist artist object
 * @param type 0 for individual, 1 for group
 */
void set_artist_type(Artist* artist, char* type);

/**
 * @brief Adds the duration of the music to the artist discography
 * 
 * @param artist artist object
 * @param duration duration in seconds
 */
void add_to_artist_discography(Artist* artist,int duration);

/**
 * @brief Get the artist discography
 * 
 * @param artist artist object
 * 
 * @return int artist discography in seconds
 */
int get_artist_discography(Artist* artist);

/**
 * @brief Check if the artist is a group
 * 
 * @param artist artist object
 * 
 * @return 1 if it is a group, 0 if it is an individual
 */
int is_group(Artist* artist);

/**
 * @brief Calculate the artist recipe
 * 
 * @param artist artist object
 * 
 * @return float artist recipe
 */
float calculate_artist_recipe(Artist* artist);

/**
 * @brief Get the number of individual albums
 * 
 * @param artist artist object
 * 
 * @return int number of individual albums
 */
int get_number_of_individual_albums(Artist* artist);

/**
 * @brief Get the number of colective musics
 * 
 * @param artist artist object
 * 
 * @return int number of colective musics
 */
int get_number_of_colective_musics(Artist* artist);

/**
 * @brief Get the artist colective music id
 * 
 * @param artist artist object
 * @param index index of the colective music
 * 
 * @return char* colective music id
 */
char* get_colective_music_id(Artist* artist, int index);

/**
 * @brief Increment in one the number of individual artist albuns
 * 
 * @param artist artist object
 */
void increment_individual_artist_albuns(Artist* artist);

/**
 * @brief Increment in one the number of individual musics reproductions
 * 
 * @param artist artist object
 */
void increment_music_reproductions(Artist* artist);

/**
 * @brief Add a group id to the artist group participation
 * 
 * @param artist artist object
 * @param group_id group id
 */
void add_to_group_participation(Artist* artist, int group_id);

/**
 * @brief Gives the artist group participation lenght
 * 
 * @param artist artist object
 * 
 * @return int group participation lenght
 */
int group_participation_lenght(Artist* artist);

/**
 * @brief Get the artist group participation index
 * 
 * @param artist artist object
 * @param index index of the group participation
 * 
 * @return int group participation index
 */
int get_group_participation_index(Artist* artist, int index);

/**
 * @brief Gives the number of artist constituents in a group
 * 
 * @param artist artist object
 * 
 * @return int number of artist constituents
 */
int get_number_of_artist_constituents(Artist* artist);

/**
 * @brief Increment the number of times the artist was on top 10
 * 
 * @param artist artist object
 */
void increment_times_on_top_10(Artist* artist);

/**
 * @brief Get the number of times the artist was on top 10
 * 
 * @param artist artist object
 * 
 * @return int number of times on top 10
 */
int get_times_on_top_10(Artist* artist);

/**
 * @brief Reset the number of times the artist was on top 10
 * 
 * @param artist artist object
 */
void reset_times_on_top_10(Artist* artist);

#endif // ARTIST_H