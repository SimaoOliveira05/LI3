#include "./queries/query_artist_on_top_10_more_often.h"
#include "./data/catalogs/catalogs_utils/determine_top_10.h"
#include "./utils/time.h"
#include "./interactive/interactive.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct query_artist_on_top_10_more_often{
    char* name;
    char* type;
    int count_top_10;
}Query_artist_on_top_10_more_often;

void free_artist_on_top_10_more_often(void* struct_to_free){

    Query_artist_on_top_10_more_often* artist_top10_often = (Query_artist_on_top_10_more_often*)struct_to_free;

    free(artist_top10_often->name);
    free(artist_top10_often->type);
    free(artist_top10_often);
    
}

char** artist_on_top_10_more_often_iterator(void* void_to_array_string, int num_to_print){

    Query_artist_on_top_10_more_often* to_array_string = (Query_artist_on_top_10_more_often*)void_to_array_string;

    char** string = malloc(num_to_print * sizeof(char*));

    string[0] = strdup(to_array_string->name);
    string[1] = strdup(to_array_string->type);

    string[2] = malloc(20 * sizeof(char));
    snprintf(string[2], 20, "%d\n", to_array_string->count_top_10);


    return string;
}

// Increment the times on top 10 of the artist
int add_to_artist_top_10(ArtistsCatalog* artistsCatalog, int artist_id) {
    Artist* artist = get_artist_by_id(artistsCatalog, artist_id);
    if (artist == NULL) return 1;
    increment_times_on_top_10(artist);

    return 0;
}

// Increment the times on top 10 of the artists that are on the top 10 between the initial and final week offset
void actualize_artist_top_10(DataBase* db, int i_week_offset, int f_week_offset) {

    if (i_week_offset == -1 || f_week_offset == -1) {
        get_min_and_max_week_offset(get_historys_catalog(db), &i_week_offset, &f_week_offset);        
    }
 
    for (int i = i_week_offset; i <= f_week_offset; i++) {
        int* top10_ids = get_top_10_by_week(get_historys_catalog(db), i);
        if (top10_ids == NULL) continue;
        for (int j = 0; j < 10; j++) {
            if (top10_ids[j] == -1) break;
            add_to_artist_top_10(get_artists_catalog(db), top10_ids[j]);
        }
    }

}

int top_10_more_often_artist_id(ArtistsCatalog* artistsCatalog, int* timesOnTop10) {
    GList* keys = g_hash_table_get_keys(get_artists(artistsCatalog));
    GList* iter = keys;

    int artist_id = 0, max_times = 0; 

    while (iter != NULL) {
        Artist* artist = get_artist_by_id(artistsCatalog, *(int*)iter->data);

        if (get_times_on_top_10(artist) > max_times || (get_times_on_top_10(artist) == max_times && *(int*)iter->data < artist_id)) {
            artist_id = get_artist_id(artist);
            max_times = get_times_on_top_10(artist);
        }

        reset_times_on_top_10(artist);
        iter = iter->next;
    }

    //Free the keys list
    g_list_free(keys);

    *timesOnTop10 = max_times;
    return artist_id;
}

int query_artist_on_top_10(void** to_fill, DataBase* db, char* input) {
    char *initial_time = NULL, *final_time = NULL;

    // Parse the input
    if (input != NULL) {
        
        // Parse the initial and final dates
        char* token = strtok(input, " ");
        if (token != NULL) {
            initial_time = strdup(token);
        }

        token = strtok(NULL, " ");
        if (token != NULL) {
            final_time = strdup(token);
        }
    }
    
    // Get the time information of the initial and final times
    int i_week_offset = get_week_offset(initial_time);
    int f_week_offset = get_week_offset(final_time);

    // Free the initial and final time strings
    free(initial_time);
    free(final_time);

    // Actualize the artist top 10
    actualize_artist_top_10(db, i_week_offset, f_week_offset);

    int timesOnTop10 = 0;
    int artist_id = top_10_more_often_artist_id(get_artists_catalog(db), &timesOnTop10);
    
    // Format the result
    char artist_id_str[20];
    snprintf(artist_id_str, sizeof(artist_id_str), "A%07d", artist_id);
    
    Query_artist_on_top_10_more_often* output = malloc(sizeof(Query_artist_on_top_10_more_often));

    if (artist_id != 0){
        Artist *artist = get_artist_by_id(get_artists_catalog(db), artist_id);
        char type[15];
        if (is_group(artist)) {
            snprintf(type, 15, "group");
        } else {
            snprintf(type, 15, "individual");
        }

        
        output->name = strdup(artist_id_str);
        output->type = strdup(type);
        output->count_top_10 = timesOnTop10;

        

    } else { 
        free(output);
        return 0;
    }

    *to_fill = output;

    return 3; 
}