#ifndef WRITER_H
#define WRITER_H

#include "./data/catalogs/catalogs_utils/parse_utils.h"

#include <stdio.h>

/**
 * @brief Writes a line in a desired file.
 * 
 * @param file_path Path to the file.
 * @param line_to_write Line to write in the file.
 */
void write_in_file(char* file_path, char* line_to_write);

/**
 * @brief Writes the response of a query in a file.
 * 
 * @param query_num Number of the query.
 * @param response Response of the query.
 */
void write_query_response(int query_num, char* response);

/**
 * @brief Writes an invalid object in a file.
 * 
 * @param type Type of the struct that caused the error. (ARTIST, USER, MUSIC)
 * @param line_to_add Line to be written.
 */
void write_error(StructType type, char* line_to_add);

#endif