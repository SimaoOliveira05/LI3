#include "./utils/strsep_by_token.h"
#include <stdlib.h>
#include <string.h>

void strsep_by_token(int* a, int*b, int*c, char* sep, char* string) {

    if (a == NULL || b == NULL || c == NULL || sep == NULL || string == NULL)
        return; // Handle NULL pointers

    *a = 0; *b = 0; *c = 0;
    
    char* token = strsep(&string, sep);
    if (token) {
        *a = atoi(token);
        token = strsep(&string, sep);
    }
    if (token) {
        *b = atoi(token);
        token = strsep(&string, sep);
    }
    if (token) {
        *c = atoi(token);
    }
}