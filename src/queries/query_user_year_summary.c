#include "./data/catalogs/catalogs_utils/history_data.h"
#include "./data/database.h"
#include "./data/catalogs/historys_catalog.h"
#include "./queries/query_user_year_summary.h"
#include "./utils/time.h"
#include "./utils/format.h"

typedef struct {
    char* user_id;
    char* year;
    int nArtists;
    int flag;
} UserYearSummary;

typedef struct top_artist_info{
    char* artist_id;
    int musicCount;
    char* listeningTime;
} Top_artist_info;


typedef struct query_user_year_summary{
    char* listening_time; 
    int music_count; 
    char* artist;
    char* day;
    char* genre; 
    char* favorite_album; 
    int hour; 
    int num_of_artist;
    Top_artist_info* artist_list;
}Query_user_year_summary;


void free_user_year_summary(UserYearSummary* to_free) {
    if (!to_free) return; // Null check

    // Free dynamically allocated strings
    free(to_free->user_id);
    free(to_free->year);

    // Finally, free the main structure
    free(to_free);
}

void free_query_user_year_summary(void* struct_to_free) {
    if (!struct_to_free) return; // Null check

    Query_user_year_summary* to_free = (Query_user_year_summary*)struct_to_free;

    // Free dynamically allocated strings
    if (to_free->listening_time) free(to_free->listening_time);
    if (to_free->artist) free(to_free->artist);
    if (to_free->day) free(to_free->day);
    if (to_free->genre) free(to_free->genre);
    if (to_free->favorite_album) free(to_free->favorite_album);
    int i = 0;
    // Free artist list elements
    if (to_free->artist_list) { // Null check for the list
        for (i = 0; i < to_free->num_of_artist; i++) {
            Top_artist_info current = to_free->artist_list[i];
            //if (current.artist_id) free(current.artist_id);
            if (current.listeningTime) free(current.listeningTime);
        }
        // Free the artist list (array itself)
        free(to_free->artist_list);
    }
    free(to_free);
}



char** user_year_summary_iterator(void* void_to_array_string, int num_to_print){

    Query_user_year_summary* to_array_string = (Query_user_year_summary*)void_to_array_string;

    char** string = malloc(num_to_print * sizeof(char*));

    string[0] = strdup(to_array_string->listening_time);
    
    string[1] = malloc(6);
    snprintf(string[1], 6, "%d", to_array_string->music_count);

    string[2] = strdup(to_array_string->artist);
    string[3] = strdup(to_array_string->day);
    string[4] = strdup(to_array_string->genre);
    string[5] = strdup(to_array_string->favorite_album);
    
    string[6] = malloc(6);
    snprintf(string[6], 6, "%02d\n", to_array_string->hour);

    if (num_to_print > 7){
        int num_artists = (num_to_print - 7) / 3;
        for (int i = 0; i < num_artists; i++){
            Top_artist_info current = to_array_string->artist_list[i];
                int base = 7 + (i * 3);
                string[base] = current.artist_id;
                
                string[base + 1] = malloc(6);
                snprintf(string[base + 1], 6, "%d", current.musicCount);

                char* temp = current.listeningTime;
                string[base + 2] = malloc(strlen(temp)+2);
                snprintf(string[base + 2], strlen(temp)+2, "%s\n", temp);
        }
    }
    
    return string;
}


UserYearSummary* format_user_year_summary(const char* input) {
    UserYearSummary* summary = malloc(sizeof(UserYearSummary));
    summary->flag = 0;
    if (!summary) return NULL;

    char* input_copy = strdup(input);
    if (!input_copy) {
        free(summary);
        return NULL;
    }

    char* token = strtok(input_copy, " ");
    summary->user_id = strdup(token);


    token = strtok(NULL, " ");
    summary->year = strdup(token);

    token = strtok(NULL, " ");
    if (token == NULL){
        summary->nArtists = 1;
        summary->flag = 1;
    }

    else
        summary->nArtists = atoi(token);

    free(input_copy);
    return summary;
}


int query_user_year_summary(void** to_fill, DataBase* db, char* input){

    UserYearSummary* summary = format_user_year_summary(input);
    int user_id = atoi(summary->user_id+1);

    //Ir buscar a respetiva lista de historicos
    GPtrArray* historyList = get_history_list_by_user(get_historys_catalog(db), user_id);


    if (historyList == NULL) {
        free_user_year_summary(summary);
        return 0;
    }
    
    HistoryData* historyData = build_history_data(historyList, db, summary->nArtists,summary->year);

    //Não foi encontrada nenhuma history relacionada a este user
    if (historyData == NULL){
        free_user_year_summary(summary);
        return 0;
    }

    Query_user_year_summary* output = malloc(sizeof(struct query_user_year_summary));

    // Get the total listening time
    output->listening_time = get_listening_time(historyData);

    // Get the total music count
    output->music_count = get_music_count(historyData);

    // Get the most listened genre
    output->genre = get_most_listened_genre(historyData);


    output->artist = get_artist_id_by_index(historyData, 0);
    //char* mostHeardArtistTime = convert_seconds_to_time(historyData->mostHeardArtists[0]->listeningTime);
    //int mostHeardArtistMusicCount = historyData->mostHeardArtists[0]->musicCount;
    
    // Get the most listened album
    output->favorite_album = get_most_heard_album(historyData); 

    output->hour = get_most_listened_hour(historyData);

    int day;
    int month;
    get_most_listened_date(historyData, &month, &day);


    output->day = malloc(11);
    snprintf(output->day, 11, "%s/%02d/%02d", summary->year,month,day);

    
    output->artist_list = NULL;

    //Verificar se foi pedido listar os top n artistas
    if (summary->flag) {
        *to_fill = output;
        free_historyData(historyData, summary->nArtists);
        free_user_year_summary(summary);
        return 7;
    }
    
    //Listar os top n artistas
    int n_artists = summary->nArtists;
    Top_artist_info* n_mostHeardArtists = malloc(sizeof(Top_artist_info) * n_artists);

    int true_artists_num = 0;
    for(int i = 0; i < n_artists; i++){
        if (get_artist_time_by_index_int(historyData, i) == 0)
            break;

        n_mostHeardArtists[i].artist_id = get_artist_id_by_index(historyData, i);
        n_mostHeardArtists[i].musicCount = get_artist_music_count_by_index(historyData, i);
        n_mostHeardArtists[i].listeningTime = get_artist_time_by_index(historyData, i);
        
        true_artists_num++;
    }

    output->artist_list = n_mostHeardArtists;

    *to_fill = output;
    
    free_historyData(historyData, summary->nArtists);
    free_user_year_summary(summary);

    output->num_of_artist = true_artists_num;

    return 7 + (true_artists_num * 3);
}