#include "./queries/query_user_recommender.h"
#include "./data/catalogs/catalogs_utils/our_recommender.h"
#include "./../recomendador/recomendador.h"
#include "./data/database.h"

#include <stdio.h>
#include <string.h>



typedef struct query_user_recommender{
    int num;
    char** id_list;
}Query_user_recommender;

typedef struct query5{
    char* user_id;
    int n_users;
}Query5;    

Query5* format_input(char* input) {
    Query5 *query = malloc(sizeof(Query5));

    // Split the input string by space
    char* token = strtok(input, " ");
    if (token != NULL) {
        query->user_id = strdup(token); // Store the username
    }

    token = strtok(NULL, " ");
    if (token != NULL) {
        query->n_users = atoi(token); // Convert the number of users to an integer and store it
    }

    return query;
}

void free_query_user_recommender(void* struct_to_free){
    Query_user_recommender* to_array_string = (Query_user_recommender*)struct_to_free;

    free(to_array_string->id_list);
    free(to_array_string);
}


char** user_recommender_iterator(void* void_to_array_string, int num_to_print){

    Query_user_recommender* to_array_string = (Query_user_recommender*)void_to_array_string;

    char** string = malloc(num_to_print * sizeof(char*));

    for (int i = 0; i < to_array_string->num; i++){
        string[i] = malloc(strlen(to_array_string->id_list[i])+2);
        snprintf(string[i], strlen(to_array_string->id_list[i])+2, "%s\n" ,to_array_string->id_list[i]);
    }

    return string;
}

int query_user_recommender_original(void** to_fill, DataBase* db, char* query_input){
    Query5* query = format_input(query_input);
    
    if (verify_if_user_exists(get_historys_catalog(db), atoi(query->user_id+1)) == 0) {
        free(query->user_id);
        free(query);
        return 0;
    }

    Recommender* recommender = get_recommender(db);

    char** recomendations = recomendaUtilizadores(query->user_id, get_recommender_matrix(recommender), get_recommender_user_ids(recommender), get_recommender_genre_names(recommender), get_recommender_num_users(recommender), get_recommender_num_genres(recommender), query->n_users);

    Query_user_recommender* output = malloc(sizeof(Query_user_recommender));

    output->id_list = recomendations;
    output->num = query->n_users;
    
    int num_of_elements = query->n_users;
    *to_fill = output;
    
    free(query->user_id);
    free(query);

    return num_of_elements;    
}




int query_user_recommender_self(void** to_fill, DataBase* db, char* query_input){
    Query5* query = format_input(query_input);
    
    if (verify_if_user_exists(get_historys_catalog(db), atoi(query->user_id+1)) == 0) {
        free(query->user_id);
        free(query);
        return 0;
    }

    RecommenderInfo* recommender = initialize_recommenderInfo(get_user_recommender(get_user_by_id(get_users_catalog(db),atoi(query->user_id+1))), atoi(query->user_id+1), query->n_users);

    g_hash_table_foreach(get_users(get_users_catalog(db)), calculate_dot_product, recommender);

    int real_user_count;
    
    char** recomendations = transform_into_string_array(recommender, &real_user_count);

    free_recommenderInfo(recommender);

    Query_user_recommender* output = malloc(sizeof(Query_user_recommender));

    output->id_list = recomendations;
    output->num = real_user_count;
    

    *to_fill = output;
    
    free(query->user_id);
    free(query);

    return real_user_count;    
}