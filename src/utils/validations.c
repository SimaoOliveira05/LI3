#include "./utils/validations.h"
#include "./utils/strsep_by_token.h"
#include <strings.h> // Include the header for strcasecmp
#include <time.h>

int date_validation(char* date){
    
    if (strlen(date) != 10) {
        return 1;
    }


    for (int i = 0; i < 10; i++) {
        if ((i == 4 || i == 7) && date[i] != '/'){
        return 1; 
        }

        if ((i != 4 && i != 7) && (date[i] < '0' || date[i] > '9')){
            return 1;
        }

    }

    int day, month, year;
    char* date_copy = strdup(date);
    strsep_by_token(&year, &month, &day, "/", date_copy);
    free(date_copy);

    if (day < 1 || day > 31 || month < 1 || month > 12 || year > 2024){
        return 1;
    }

    return 0;
}


int time_validation(char* time) {
    for (int i = 0; i < 8; i++) {
        if (((i == 2 || i == 5) && time[i] != ':') || (((i!=2 && i != 5) && (time[i] < '0' || time[i] > '9')))) {
            return 1;
        }
    }

    int hours, minutes, seconds;
    char* time_copy = strdup(time);
    strsep_by_token(&hours, &minutes, &seconds, ":", time_copy);
    free(time_copy);

    if (hours < 0 || hours > 99 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59) {
        return 1;
    }
    return 0;
}


int email_validation(char* email) {
    int at = 0, dot = 0, lstring = 0, rstring = 0;
    for (size_t i = 0; i < strlen(email); i++) {
        if (email[i] == '@') {
            at++;
            continue;
        }
        if (email[i] == '.') {
            dot++;
            continue;
        }
        if (at != 0) lstring++;
        if (at != 0 && dot != 0) rstring++;
        //Antes estava a dar errado porque não verificava os numeros, só se estava entre "a" e "z"
        if ((email[i] < 'a' || email[i] > 'z') && (email[i] < '0' || email[i] > '9')) {
            return 1;
        }
    }
    // Verifica se há pelo menos um '@' e um '.'
    if (at != 1 || dot != 1 || lstring < 1 || (rstring != 2 && rstring != 3)) {
        return 1;
    }
    return 0;
}

int subscription_type_validation(char* type) {
    return (strcmp(type, "normal") == 0 || strcmp(type, "premium") == 0);
}


int artist_id_validation(char* id_constituint, char* type) {

    return (strcmp(id_constituint,"[]") == 0 && strcmp(type,"group")) 
                || (strcmp(id_constituint,"[]") != 0 && strcmp(type,"individual"));
}


int platform_validation(char* platform) {
    return (strcasecmp(platform,"mobile") == 0 || strcasecmp(platform,"desktop") == 0);
}

int type_validation(char* type) {
    return (strcasecmp(type,"individual") == 0 || strcasecmp(type,"group") == 0);
}