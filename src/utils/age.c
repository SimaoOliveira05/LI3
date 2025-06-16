#include <stdlib.h>
#include <string.h>
#include "./utils/age.h"
#include "./utils/strsep_by_token.h"


int calculate_age(char* date) {
    int day = 0, month = 0, year = 0;
    char* date_copy = strdup(date);
    strsep_by_token(&year, &month, &day, "/", date_copy);
    free(date_copy);

    int age = 2024 - year;
    if (month > 9 || (month == 9 && day > 9)) 
        age--;

    free(date);
    return age;
}

