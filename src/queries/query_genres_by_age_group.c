#include "./queries/query_genres_by_age_group.h"
#include <stdio.h>

typedef struct query_genres_by_age_group {
    GenreLikes* ordered_list;
    int num_of_elems;
} Query_genres_by_age_group;


void free_query_genres_by_age_group(void* to_free) {
    Query_genres_by_age_group* to_free_struct = (Query_genres_by_age_group*)to_free;
    free(to_free_struct->ordered_list);
    free(to_free_struct);
}

char** genre_by_age_group_iterator(void* void_to_array_string, int num_to_print){

    Query_genres_by_age_group* to_array_string = (Query_genres_by_age_group*)void_to_array_string;

    char** string = malloc(num_to_print * sizeof(char*));
    GenreLikes* genres = to_array_string->ordered_list;
    for (int i = 0; i < num_to_print/2; i++){
        GenreLikes* genre = genre_likes_get_element(genres, i);
        string[i*2] = strdup(genre_likes_get_genre(genre));
        string[i*2+1] = malloc(12); 
        snprintf(string[i*2 + 1], 12, "%d\n", genre_likes_get_likes(genre));
    }

    return string;
}



int query_genre_by_age_group(void** to_fill, DataBase* db, char* input) {
    int min_age = -1, max_age = -1;

    // Parse input for age ranges
    char* token = strtok(input, " ");
    if (token != NULL) {
        min_age = atoi(token); // Store the first token in min_age
    }

    token = strtok(NULL, "\"");
    if (token != NULL) {
        max_age = atoi(token); // Store the quoted string in max_age
    }

    if (min_age == -1 || max_age == -1) {
        return 0; // Fixed error handling
    }

    Query_genres_by_age_group* output = malloc(sizeof(Query_genres_by_age_group));
    if (!output) return -1; 
    

    // Get the genres and likes for the specified age group
    output->ordered_list = genre_by_age_group(get_musics_catalog(db), min_age, max_age);
    if (!output->ordered_list){
        free(output);
        return 0;
    }


    *to_fill = output;
    int num_of_genres = get_number_of_genres(get_musics_catalog(db));
    output->num_of_elems = num_of_genres;
    return num_of_genres * 2;
}