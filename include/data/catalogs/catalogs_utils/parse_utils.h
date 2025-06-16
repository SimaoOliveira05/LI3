#ifndef PARSEUTILS_H
#define PARSEUTILS_H

#include "./data/database.h"

/**
 * @brief Enum to define the type of file we are parsing
 * 
 */
typedef enum {
    MUSIC,
    ARTIST,
    USER,
    HISTORY,
    ALBUM,
} StructType;

/**
 * @brief Converts a string of artist IDs into an array of strings.
 * 
 * This function takes a string of artist IDs in the format "['A0000497', 'A0000030']"
 * and returns a dynamically allocated array of strings in the format ["A000497", "A000030", ...].
 * The array is managed by GLib and will automatically resize if necessary.
 * 
 * @param artist_ids_str The input string containing artist IDs.
 * @return GPtrArray* A dynamically allocated array of strings containing the artist IDs.
 */
GArray* format_ids_list(const char* artist_ids_str);

#endif