#include "./queries/query_person_summary.h"
#include "./utils/age.h"
#include "./interactive/interactive.h"
#include <stdio.h>
#include <math.h>
#include "./queries/query_person_summary.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>


typedef struct user_summary{
    char* user_email;
    char* user_last_name;
    int user_age;
}User_summary;

typedef struct artist_summary{
    char* artist_is_group;
    int artist_num_albums_individuals;
    float artist_total_recipe;
}Artist_summary;

typedef struct query_person_summary{
    
    int type; // 0 -> User ; 1 -> Artist
    char* name;
    char* country;
    void* specific_summary;
}Query_person_summary;


float round_to_decimal_places(float number, int decimal_places) {
    float factor = pow(10, decimal_places);
    return round(number * factor) / factor;
}

Query_person_summary* initialize_query_person_summary() {

    Query_person_summary* query_summary = malloc(sizeof(Query_person_summary));

    query_summary->type = 0;            
    query_summary->name = NULL;        
    query_summary->country = NULL;     
    query_summary->specific_summary = NULL;

    return query_summary;
}

void free_person_summary(void* struct_to_free){

    Query_person_summary* query_summary = (Query_person_summary*)struct_to_free;
    
    if (!query_summary) return; 

    // Free common fields
    if (query_summary->name) 
        free(query_summary->name);
    if (query_summary->country) 
        free(query_summary->country);

    // Free specific_summary based on type
    if (query_summary->specific_summary){
        if (query_summary->type == 0) { // User
            User_summary* user = (User_summary*)query_summary->specific_summary;

            if (user->user_email)
                free(user->user_email);
            if (user->user_last_name)
                free(user->user_last_name);

            free(user);
        } else if (query_summary->type == 1) { // Artist
            Artist_summary* artist = (Artist_summary*)query_summary->specific_summary;
            if (artist->artist_is_group){
                free(artist->artist_is_group);
            }
            free(artist);
        }
    }
    free(query_summary);
}


char** person_summary_iterator(void* void_to_array_string, int num_to_print){

    Query_person_summary* to_array_string = (Query_person_summary*)void_to_array_string;

    char** string = malloc(num_to_print * sizeof(char*));
    if (to_array_string->type == 0){
        User_summary* user_summary = (User_summary*)to_array_string->specific_summary;
        string[0] = strdup(user_summary->user_email);
        string[1] = strdup(to_array_string->name);
        string[2] = strdup(user_summary->user_last_name);

        string[3] = malloc(20 * sizeof(char));
        snprintf(string[3], 20, "%d", user_summary->user_age);
        
        string[4] = malloc(strlen(to_array_string->country) + 2);
        snprintf(string[4], strlen(to_array_string->country) + 2, "%s\n", to_array_string->country);

    }else{ 
        Artist_summary* artist_summary = (Artist_summary*)to_array_string->specific_summary;
        string[0] = strdup(to_array_string->name);
        string[1] = strdup(artist_summary->artist_is_group);
        string[2] = strdup(to_array_string->country);

        string[3] = malloc(20 * sizeof(char));
        snprintf(string[3], 20, "%d", artist_summary->artist_num_albums_individuals);

        string[4] = malloc(20);
        snprintf(string[4], 20, "%.2f\n", round_to_decimal_places(artist_summary->artist_total_recipe, 2));
        
    }
    
    return string;
}

Query_person_summary* format_user_summary(User* user){
    Query_person_summary* output = initialize_query_person_summary();
    
    User_summary* user_output = malloc(sizeof(User_summary));

    output->type = 0;
    user_output->user_email = get_user_email(user);
    output->name = get_user_first_name(user);
    user_output->user_last_name = get_user_last_name(user);
    user_output->user_age = calculate_age(get_user_birth_date(user));
    output->country = get_user_country(user);

    output->specific_summary = user_output;

    return output;
}

Query_person_summary* format_artist_summary(ArtistsCatalog* catalog, Artist* artist){
    
    Query_person_summary* output = initialize_query_person_summary();
    
    Artist_summary* artist_output = malloc(sizeof(Artist_summary));

    output->type = 1;
    output->name = get_artist_name(artist);
    output->country = get_artist_country(artist);
    artist_output->artist_is_group = strdup(is_group(artist) ? "group" : "individual"); 
    artist_output->artist_num_albums_individuals = get_number_of_individual_albums(artist);
    artist_output->artist_total_recipe = round_to_decimal_places(calculate_recipe(catalog, artist), 2);
    output->specific_summary = artist_output;
    
    return output; 
}


int query_person_summary (void** to_fill, DataBase* db, char* id) {
    Query_person_summary* output = NULL;

    switch (id[0]) {
        case 'U': {
            int id_num = atoi(id+1);
            User* user = get_user_by_id(get_users_catalog(db), id_num);
            if (user == NULL) goto default_case;
            output = format_user_summary(user);
            break;
        }
        case 'A': {
            int id_num = atoi(id+1);
            Artist* artist = get_artist_by_id(get_artists_catalog(db), id_num);
            if (artist == NULL) goto default_case;
            output = format_artist_summary(get_artists_catalog(db),artist);
            break;
        }
        default:
        default_case:
            return 0;
            break;
    }

    *to_fill = output;
    return 5;    
}