#ifndef CMP
#define CMP

#include <glib.h>

/**
 * @brief Compares two integer pointers with additional user data.
 *
 * This function compares two integer pointers and returns the result of the comparison.
 * The user_data parameter is not used in this function.
 *
 * @param a Pointer to the first integer.
 * @param b Pointer to the second integer.
 * @param user_data Additional user data (unused).
 * @return A negative value if the first integer is less than the second,
 *         zero if they are equal, or a positive value if the first integer is greater.
 */
gint cmp_int(gconstpointer a, gconstpointer b);

/**
 * @brief Compares two strings representing integers.
 *
 * This function converts two strings to integers and returns the result of the comparison.
 *
 * @param a Pointer to the first string.
 * @param b Pointer to the second string.
 * @return A negative value if the first integer is less than the second,
 *         zero if they are equal, or a positive value if the first integer is greater.
 */
gint cmp_int_pointer_with_data(gconstpointer a, gconstpointer b, gpointer user_data);

/**
 * @brief Compares two strings.
 *
 * This function compares two strings and returns the result of the comparison.
 *
 * @param a Pointer to the first string.
 * @param b Pointer to the second string.
 * @param user_data Additional user data (unused).
 * @return A negative value if the first string is less than the second,
 *         zero if they are equal, or a positive value if the first string is greater.
 */
gint strcmp_wrapper(gconstpointer a, gconstpointer b, gpointer user_data);

#endif // CMP