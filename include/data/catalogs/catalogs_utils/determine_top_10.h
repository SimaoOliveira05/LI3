#ifndef DETERMINE_TOP_10_H
#define DETERMINE_TOP_10_H

#include <glib.h>

/**
 * @brief Struct that contais the artistTree, a tree with the artists ids and their total audition duration, and the minimum and maximum week offset of the historys catalog.
 * 
 */
typedef struct top10Struct Top10Struct;

/**
 * @brief Frees the memory allocated for the top 10 struct.
 * 
 * @param data The top 10 struct to be freed.
 */
void free_top10_struct(gpointer data);

/**
 * @brief Creates a top 10 struct object.
 * 
 * @return Top10Struct* The top 10 struct object.
 */
Top10Struct* create_top10_struct();

/**
 * @brief Given a week offset, returns a tree with the artists and their total audition duration.
 * 
 * @param top10Struct The top 10 struct.
 * @param week_offset The week offset.
 * 
 * @return GTree* The tree with the artists and their total audition duration.
 */
GTree* get_artistDurationTree_by_week(Top10Struct *top10Struct, int week_offset);

/**
 * @brief Gives the minimum and maximum week offset from the top 10 struct.
 * 
 * @param top10Struct The top 10 struct.
 * @param min_week_offset The minimum week offset.
 * @param max_week_offset The maximum week offset.
 */
void get_min_and_max_week_offset_from_top10(Top10Struct* top10Struct, int* min_week_offset, int* max_week_offset);

/**
 * @brief Gets the weeks with history from the top 10 struct.
 * 
 * @param top10Struct The top 10 struct.
 */
GList* get_weeks_with_history(Top10Struct* top10Struct);

/**
 * @brief Given a week offset, returns the top 10 artists.
 * 
 * @param top10Struct The top 10 struct.
 * @param week_offset The week offset.
 * 
 * @return int* The top 10 artists.
 */
int* get_top_10_by_week_from_top10(Top10Struct *top10Struct, int week_offset);

/**
 * @brief Adds an artist to the artist tree.
 * 
 * @param artistTree The artist tree.
 * @param artist_id The artist id.
 * @param duration The duration.
 */
void add_to_artistDurationTree_struct_from_top10(Top10Struct* top10Struct, int week_offset, int artist_id, int duration);

/**
 * @brief Actualize minimum and maximum week offset.
 * 
 * @param top10Struct The top 10 struct.
 * @param week_offset The actual week offset.
 */
void actualize_min_and_max_week_offset(Top10Struct* top10Struct, int week_offset);

#endif //DETERMINE_TOP_10_H