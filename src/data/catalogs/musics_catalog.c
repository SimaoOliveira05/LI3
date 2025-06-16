#include "./data/catalogs/musics_catalog.h"
#include "./utils/validations.h" 
#include "./utils/time.h"


typedef struct musicsCatalog {
    GHashTable *musics;
    GHashTable *genres;
    GHashTable *genreTable;
    int genres_count;
} MusicsCatalog; 

// Create a new music catalog with all the data structures initialized
MusicsCatalog* create_music_catalog() {
    MusicsCatalog* catalog = g_malloc(sizeof(MusicsCatalog));
    catalog->musics = g_hash_table_new_full(g_int_hash, g_int_equal, g_free, (GDestroyNotify)free_music);
    catalog->genres = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    catalog->genreTable = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    catalog->genres_count = 0;
    return catalog;
}

// Free the memory allocated for the catalog and all the data structures inside
void free_musics_catalog(MusicsCatalog* catalog){
    // Free the music hash table
    g_hash_table_destroy(catalog->musics);
    g_hash_table_destroy(catalog->genreTable);

    // Free the genre hash table
    GList* values = g_hash_table_get_values(catalog->genres);
    for (GList* l = values; l != NULL; l = l->next) {
        free_liked_musics_list((LikedMusicsList*)l->data);
    }
    g_list_free(values);
    g_hash_table_destroy(catalog->genres);

    // Free the catalog 
    free(catalog);
}

void insert_to_musics_catalog (MusicsCatalog* catalog,Music* music){
    int* key =g_new(int, 1);
    *key = get_music_id(music);
    g_hash_table_insert(catalog->musics,key,music);
}

Music *get_music_by_id(MusicsCatalog* catalog, int id){
    int* key =g_new(int, 1);
    *key = id;
    Music* music = g_hash_table_lookup(catalog->musics,key);
    g_free(key);
    return music;
}

void insert_to_genres_music_catalog(MusicsCatalog* catalog, char* genre) {
    LikedMusicsList* liked_musics_list = initialize_liked_musics_list();
    char* genre_copy = strdup(genre);
    g_hash_table_insert(catalog->genres, genre_copy, liked_musics_list);
}

LikedMusicsList* get_genre_liked_musics_list(MusicsCatalog* catalog, char* genre) {
    return g_hash_table_lookup(catalog->genres, genre);
}


int search_on_genres_music_catalog(MusicsCatalog* catalog, char* genre) {
    return g_hash_table_contains(catalog->genres, genre);
}

int get_number_of_genres(MusicsCatalog* catalog){
    return (int)g_hash_table_size(catalog->genres);
}


void update_genres_music_catalog(MusicsCatalog* catalog, char* genre, int age) {
    
    LikedMusicsList* liked_musics_list = get_genre_liked_musics_list(catalog, genre);
    
    liked_musics_list = insert_to_liked_musics_list(liked_musics_list, age);
    
    // Replace the old LikedMusicsList with the updated one in the hash table
    char* genre_copy = strdup(genre);
    g_hash_table_replace(catalog->genres, genre_copy, liked_musics_list);
    
    free(genre);
}

gboolean valid_music_id (MusicsCatalog* musicCatalog,int id){
    int *key = g_new(int, 1);
    *key = id;
    gboolean is_valid = g_hash_table_contains(musicCatalog->musics,key);
    g_free(key);
    return is_valid;
}

int valid_musics(GArray *musics_ids, MusicsCatalog* catalog){
    for(guint index = 0; index < musics_ids->len; index++){

        if(!valid_music_id(catalog , g_array_index(musics_ids,int,index))){
            return 0;   
        }
    }        
    return 1;
}


typedef struct genreLikes{
    char* genre;
    int likes;
} GenreLikes;

char* genre_likes_get_genre(GenreLikes* genre_likes){
    return genre_likes->genre;
}

int genre_likes_get_likes(GenreLikes* genre_likes){
    return genre_likes->likes;
}

GenreLikes* genre_likes_get_element(GenreLikes* array, int index) {
    return &array[index]; 
}

void free_genre_like_array(GenreLikes* genre_like_array, int num_of_elems) {
    for (int i = 0; i < num_of_elems; i++) {
        free(&genre_like_array[i]);
    }
    free(genre_like_array);
}

int compare_genre_likes(const void* a, const void* b) {
    const GenreLikes* genre_a = (const GenreLikes*)a;
    const GenreLikes* genre_b = (const GenreLikes*)b;

    if (genre_a->likes == genre_b->likes) {
        return strcmp(genre_a->genre, genre_b->genre);
    } else {
        return genre_b->likes - genre_a->likes;
    }
}   

GenreLikes* genre_by_age_group(MusicsCatalog* catalog, int min_age, int max_age) {
    // Get the keys of the genres hash table
    int result_count = 0;
    GList* keys = g_hash_table_get_keys(catalog->genres);
    GList* iter = keys;

    // Temporary array to store GenreLikes
    GArray* genre_likes_array = g_array_new(FALSE, FALSE, sizeof(GenreLikes));

    // Populate the array with genres and their likes
    while (iter != NULL) {
        int likes = get_likes_by_age_group(get_genre_liked_musics_list(catalog, (char*)iter->data), min_age, max_age);
        if (likes > 0) {
            GenreLikes genre_likes = {(char*)iter->data, likes};
            g_array_append_val(genre_likes_array, genre_likes);
        }
        iter = iter->next;
    }
    // Sort the array by likes in decreasing order
    if (genre_likes_array->len == 0) return NULL;
    g_array_sort(genre_likes_array, (GCompareFunc)compare_genre_likes);

    // Allocate memory for the result array
    result_count = genre_likes_array->len;
    GenreLikes* result = malloc(sizeof(GenreLikes) * (result_count));
    if (result == NULL){
        g_array_free(genre_likes_array, TRUE);
        g_list_free(keys);
        return NULL; // Handle memory allocation failure
    }

    // Copy data from GArray to the result array
    for (guint i = 0; i < genre_likes_array->len; i++){
        result[i] = g_array_index(genre_likes_array, GenreLikes, i);
    }

    // Free the temporary array and keys list
    g_array_free(genre_likes_array, TRUE);
    g_list_free(keys);

    return result;
}

char* get_music_genre_by_id(MusicsCatalog* catalog, int id){
    Music* music = get_music_by_id(catalog, id);
    return get_music_genre(music);
}

void verify_or_add_genre(MusicsCatalog* catalog, char* genre) {
    if (g_hash_table_contains(catalog->genreTable, genre)) {
        return;
    }
    else{
        char* genre_copy = strdup(genre);
        g_hash_table_insert(catalog->genreTable, genre_copy, NULL);
        catalog->genres_count++;
    } 
}

int get_genres_count(MusicsCatalog* catalog) {
    return catalog->genres_count;
}


