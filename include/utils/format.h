#ifndef FORMAT_H
#define FORMAT_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Transforms an integer into a string with the format "00000000".
 * 
 * @param value Album id integer
 * @return char* Album id in string format "AL000000"
 */
char* format_album_id(int value);

/**
 * @brief Transforms an integer into a string with the format "00000000".
 * 
 * @param value Artist id integer
 * @return char* Artist id in string format "A000000"
 */
char* format_artist_id(int value);

/**
 * @brief Transforms an integer into a string with the format "00000000".
 * 
 * @param value User id integer
 * @return char* User id in string format "U000000"
 */
char* format_user_id(int value);

#endif