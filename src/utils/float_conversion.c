#include "./utils/float_conversion.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convert_string_to_float(const char* str, float* result) {
    char* endptr;
    errno = 0; // To distinguish success/failure after the call
    float value = strtof(str, &endptr);

    // Check for various possible errors
    if (endptr == str) {
        // No digits were found
        fprintf(stderr, "No digits were found in the input string: %s\n", str);
        return -1;
    } else if (errno == ERANGE) {
        // The value is out of range
        fprintf(stderr, "The value is out of range: %s\n", str);
        return -1;
    } else if (errno != 0 && value == 0) {
        // Some other error occurred
        perror("strtof");
        return -1;
    }

    *result = value;
    return 0;
}
