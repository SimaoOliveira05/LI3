#include "./utils/format.h"


// Function to format an integer as a string with a prefix and leading zeros
char* format_album_id(int value) {
    char* formatted_id = malloc(10 * sizeof(char)); // Allocate memory for the formatted string
    if (!formatted_id) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    snprintf(formatted_id, 10, "AL%06d", value); // Format the string with the prefix "AL" and leading zeros
    return formatted_id;
}


// Function to format an integer as a string with a prefix and leading zeros
char* format_artist_id(int value) {
    char* formatted_id = malloc(10 * sizeof(char)); // Allocate memory for the formatted string
    if (!formatted_id) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    snprintf(formatted_id, 10, "A%07d", value); // Format the string with the prefix "A" and leading zeros
    return formatted_id;
}


char* format_user_id(int value){
    char* formatted_id = malloc(10 * sizeof(char)); // Allocate memory for the formatted string
    if (!formatted_id) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    snprintf(formatted_id, 10, "U%07d", value); // Format the string with the prefix "U" and leading zeros
    return formatted_id;
}