#include "./data/elements/user.h"
#include "./data/catalogs/catalogs_utils/our_recommender.h"
#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "./utils/format.h"
#include "./utils/cmp.h"



typedef struct userRecommender{
    GTree* genreList;
    GTree* countryList;
    GTree* musicList;
} UserRecommender;


typedef struct dotProduct{
    int user_id;
    int dot_product;
} DotProduct;


typedef struct recommenderInfo{
    DotProduct** user_dot_product_list;
    int user_count;
    UserRecommender
* main_user;
    int main_user_id;
} RecommenderInfo;


// Comparison function for integers
gint g_int_compare(gconstpointer a, gconstpointer b, gpointer user_data) {
    (void) user_data;
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;

    return (int_a > int_b) - (int_a < int_b);
}


UserRecommender* initialize_user_recommender(){
    UserRecommender
* recommender = g_new(UserRecommender
,1);
    recommender->genreList = g_tree_new_full(strcmp_wrapper, NULL, g_free, g_free);
    recommender->countryList = g_tree_new_full(strcmp_wrapper, NULL, g_free, g_free);
    recommender->musicList = g_tree_new_full((GCompareDataFunc)g_int_compare, NULL, g_free, g_free);
    return recommender;
}

void free_user_recommender(UserRecommender *recommender) {
    g_tree_destroy(recommender->genreList);
    g_tree_destroy(recommender->countryList);
    g_tree_destroy(recommender->musicList);
    g_free(recommender);
}

DotProduct* initialize_dot_product(){
    DotProduct* dot_product = g_new(DotProduct,1);
    dot_product->user_id = -1;
    dot_product->dot_product = 0;
    return dot_product;
}

DotProduct** initialize_dot_product_list(int user_count){
    DotProduct** user_dot_product_list = g_new(DotProduct*, user_count);
    for (int i = 0; i < user_count; i++){
        user_dot_product_list[i] = initialize_dot_product();
    }
    return user_dot_product_list;
}


void free_dot_product_list(DotProduct** user_dot_product_list, int user_count){
    for (int i = 0; i < user_count; i++){
        g_free(user_dot_product_list[i]);
    }
    g_free(user_dot_product_list);
}



RecommenderInfo* initialize_recommenderInfo(UserRecommender* main_user, int main_user_id, int user_count){
    RecommenderInfo* recommenderInfo = g_new(RecommenderInfo,1);
    recommenderInfo->user_dot_product_list = initialize_dot_product_list(user_count);
    recommenderInfo->user_count = user_count;
    recommenderInfo->main_user = main_user;
    recommenderInfo->main_user_id = main_user_id;
    return recommenderInfo;
}

void free_recommenderInfo(RecommenderInfo* recommenderInfo){
    free_dot_product_list(recommenderInfo->user_dot_product_list, recommenderInfo->user_count);
    g_free(recommenderInfo);
}


void add_to_user_genre_recommender(User* user, char* genre, int listeningTime){
    int *genrelisteningTime = g_tree_lookup(get_user_recommender(user)->genreList, genre);
    if (genrelisteningTime == NULL){ 
        int *listeningTime_ptr = g_new(int,1);
        *listeningTime_ptr = listeningTime;
        g_tree_insert(get_user_recommender(user)->genreList, genre, listeningTime_ptr);
    }
    else{
        *genrelisteningTime += listeningTime;
        free(genre);
    }

}

void add_to_user_country_recommender(User* user, char* country, int listeningTime){
    int *countrylisteningTime = g_tree_lookup(get_user_recommender(user)->countryList, country);
    if (countrylisteningTime == NULL){
        int *listeningTime_ptr = g_new(int,1);
        *listeningTime_ptr = listeningTime;
        g_tree_insert(get_user_recommender(user)->countryList, country, listeningTime_ptr);
    }
    else{
        *countrylisteningTime += listeningTime;
        free(country);
    }
}

void add_to_user_music_recommender(User* user, int music_id, int listeningTime){
    int* music_id_ptr = g_new(int,1);
    *music_id_ptr = music_id;

    int *musiclisteningTime = g_tree_lookup(get_user_recommender(user)->musicList, music_id_ptr);
    if (musiclisteningTime == NULL){
        int *listeningTime_ptr = g_new(int,1);
        *listeningTime_ptr = listeningTime;
        g_tree_insert(get_user_recommender(user)->musicList, music_id_ptr, listeningTime_ptr);
    }
    else{
        *musiclisteningTime += listeningTime;
        g_free(music_id_ptr);
    }
}   


gboolean calculate_dot_product_callback(gpointer key, gpointer value, gpointer data) {
    char *current = (char *)key;
    int *current_count = (int *)value;

    struct {
        UserRecommender
     *user2;
        int *dot_product;
    } *callback_data = data;

    UserRecommender
 *user2 = callback_data->user2;
    int *dot_product = callback_data->dot_product;

    int *user2_count = g_tree_lookup(user2->genreList, current);
    if (user2_count != NULL) {
        *dot_product += (*current_count) * (*user2_count);
    }

    return FALSE;
}

int calculate_genreList_dot_product(UserRecommender *user1, UserRecommender *user2) {


    int dot_product = 0;

    struct {
        UserRecommender
     *user2;
        int *dot_product;
    } callback_data = { user2, &dot_product };

    g_tree_foreach(user1->genreList, calculate_dot_product_callback, &callback_data);

    return dot_product;
}


int calculate_countryList_dot_product(UserRecommender *user1, UserRecommender *user2) {

    int dot_product = 0;

    struct {
        UserRecommender
     *user2;
        int *dot_product;
    } callback_data = { user2, &dot_product };

    g_tree_foreach(user1->countryList, calculate_dot_product_callback, &callback_data);

    return dot_product;
}


gboolean calculate_music_dot_product_callback(gpointer key, gpointer value, gpointer data) {
    int *current_music_id = (int *)key;
    int *current_count = (int *)value;

    struct {
        UserRecommender
     *user2;
        int *dot_product;
    } *callback_data = data;

    UserRecommender
 *user2 = callback_data->user2;
    int *dot_product = callback_data->dot_product;

    int *user2_count = g_tree_lookup(user2->musicList, current_music_id);
    if (user2_count != NULL) {
        *dot_product += (*current_count) * (*user2_count);
    }
    return FALSE;
}

int calculate_musicList_dot_product(UserRecommender *user1, UserRecommender *user2) {
    int dot_product = 0;

    struct {
        UserRecommender
     *user2;
        int *dot_product;
    } callback_data = { user2, &dot_product };

    g_tree_foreach(user1->musicList, calculate_music_dot_product_callback, &callback_data);

    return dot_product;
}




void add_dot_product(DotProduct** user_dot_product_list, int user_id, int dot_product, int user_count){
    int min = user_dot_product_list[0]->dot_product;
    int min_index = 0;
    for (int i = 0; i < user_count; i++){
        if (user_dot_product_list[i]->dot_product < min){
            min = user_dot_product_list[i]->dot_product;
            min_index = i;
        }
    }
    if (dot_product > min){
        user_dot_product_list[min_index]->user_id = user_id;
        user_dot_product_list[min_index]->dot_product = dot_product;
    }
}


void calculate_dot_product(gpointer key, gpointer value, gpointer user_data){
    (void) key;
    User* user2 = (User*)value;
    RecommenderInfo* recommenderInfo = (RecommenderInfo*)user_data;

    if (recommenderInfo->main_user_id == get_user_username(user2)){
        return;
    }

    int genre_dot_product = calculate_genreList_dot_product(recommenderInfo->main_user, get_user_recommender(user2));
    int country_dot_product = calculate_countryList_dot_product(recommenderInfo->main_user, get_user_recommender(user2));
    int music_dot_product = calculate_musicList_dot_product(recommenderInfo->main_user, get_user_recommender(user2));

    int dot_product = genre_dot_product*0.5 + country_dot_product*0.3 + music_dot_product*0.2;

    add_dot_product(recommenderInfo->user_dot_product_list, get_user_username(user2), dot_product, recommenderInfo->user_count);
}


int sort_dot_product_list(DotProduct** user_dot_product_list, int user_count){
    for (int i = 0; i < user_count; i++){
        for (int j = i+1; j < user_count; j++){
            if (user_dot_product_list[i]->dot_product < user_dot_product_list[j]->dot_product){
                DotProduct* temp = user_dot_product_list[i];
                user_dot_product_list[i] = user_dot_product_list[j];
                user_dot_product_list[j] = temp;
            }
        }
    }

    for (int i = 0; i < user_count; i++){
        if (user_dot_product_list[i]->dot_product == 0){
            return i;
        }
    }
    return user_count;
}

char** transform_into_string_array(RecommenderInfo* recommenderInfo, int* real_user_count){
    
    int user_count = sort_dot_product_list(recommenderInfo->user_dot_product_list, recommenderInfo->user_count);
    *real_user_count = user_count;

    char** string_array = malloc(sizeof(char*)*user_count);
    for (int i = 0; i < user_count; i++){
        
        string_array[i] = g_new(char, 30);
        char* user_id = format_user_id(recommenderInfo->user_dot_product_list[i]->user_id);
        snprintf(string_array[i], 30, "%s", user_id);
        free(user_id);
        
    }
    return string_array;
}
