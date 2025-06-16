#ifndef FLOAT_CONVERSION
#define FLOAT_CONVERSION

/**
 * @brief Converts a string to a float.
 *
 * This function attempts to convert the input string to a float value.
 * It handles various error conditions and reports them accordingly.
 *
 * @param str The input string to be converted.
 * @param result Pointer to a float where the converted value will be stored.
 * @return 0 on success, -1 on failure.
 */
int convert_string_to_float(const char* str, float* result);

#endif //FLOAT_CONVERSION