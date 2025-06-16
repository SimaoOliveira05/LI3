#ifndef PARSER_H
#define PARSER_H

#include "./data/catalogs/catalogs_utils/parse_utils.h"
#include "./data/database.h"

/**
 * @brief Validates and adds data to the database.
 *
 * This generic function validates the provided tokens and adds the data
 * to the database if valid. It handles different data types by detecting
 * the type from the token and calling the appropriate validation function.
 *
 * @param tokens The array of tokens parsed from the input line.
 * @param database A pointer to the database where data should be added.
 * @param line The original line of input data.
 * @return 0 if the data is valid, 1 if it is not, -1 if you dont want it to print out the invalid lines.
 */
int validate_and_add (char** tokens, void* database, char* line);

/**
 * @brief Function that processes a line of a file and adds it do the DataBase
 * 
 * @param tokens List of strings to parse and transform into the correct parameters.
 * @param line parser function will store the whole line here in case it is needed.
 * @param database Database where the object will be added
 * @return Should be 1 if the line is not valid, 0 otherwise (return -1 if you dont have validations).
 */
typedef int (*ProcessLineFunc)(char** tokens, void* database, char* line);

/**
 * @brief Generic parser function to process a CSV file and add data to a database.
 *
 * This function reads a CSV file line by line, tokenizes each line, and processes
 * the tokens using a provided function pointer. It handles the header line to determine
 * the number of tokens and processes each subsequent line accordingly.
 *
 * @param database A pointer to the database where data should be added.
 * @param path The path to the CSV file to be parsed.
 * @param process_line A function pointer to the function that processes each line of tokens,keep in mind that if there is a * header, it needs to handle it too.
 * @return int Returns 0 on success, or 1 if there was an error opening the file.
 */
int parser(void* database,char* path,ProcessLineFunc process_line);

#endif