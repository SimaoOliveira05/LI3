#ifndef STRSEP_BY_TOKEN_H
#define STRSEP_BY_TOKEN_H

/**
 * @brief Splits a string by a specified separator and converts the tokens to integers.
 * 
 * This function takes a string and a separator, splits the string by the separator,
 * and converts the resulting tokens to integers. The integers are stored in the
 * provided pointers a, b, and c. If any of the pointers or the input strings are NULL,
 * the function returns immediately.
 * 
 * @param a Pointer to an integer where the first token will be stored.
 * @param b Pointer to an integer where the second token will be stored.
 * @param c Pointer to an integer where the third token will be stored.
 * @param sep The separator string used to split the input string.
 * @param string The input string to be split and converted.
 */
void strsep_by_token(int* a, int*b, int*c, char* sep, char* string);

#endif