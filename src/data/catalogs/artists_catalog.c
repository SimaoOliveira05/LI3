#include "./data/catalogs/artists_catalog.h"
#include "./utils/type.h"
#include "./utils/time.h"


typedef struct artistsCatalog {
    GHashTable *artists;
    GPtrArray *sorted_discography_array; 
} ArtistsCatalog;

void add_music_duration(ArtistsCatalog* catalog,int id,int duration){
    //Vê qual é o respetivo artista
    Artist* artist = get_artist_by_id(catalog,id);
    //Adiciona a duração da música á sua discografia
    add_to_artist_discography(artist,duration);
    
}

void add_music_duration_to_artist_list (GArray* artist_ids, ArtistsCatalog* catalog, int duration){
    for (guint i = 0; i < artist_ids->len;i++){
        int artist_id = g_array_index(artist_ids,int, i);

        add_music_duration(catalog,artist_id,duration);
    }
}

// Função de callback para iterar sobre a hash table
void add_to_artist_discography_array(gpointer key, gpointer value, gpointer user_data) {
    
    (void)key; // Avoid unused variable warning

    ArtistsCatalog* catalog = (ArtistsCatalog*)user_data; // Define o que é user_data


    Artist* artist = (Artist*)value; // Define o que tem "dentro" da hash table

    int artist_id = get_artist_id(artist);
    char* artist_name = get_artist_name(artist);
    char* artist_country = get_artist_country(artist);
    
    ArtistDiscography* artist_discography = create_artist_discography( // Cria um elemento do tipo artist_discography, armazenando apenas o necessário
        artist_id,
        artist_name,
        get_artist_type(artist),
        get_artist_discography(artist),
        artist_country
    );

    free(artist_name);
    free(artist_country);

    g_ptr_array_add(catalog->sorted_discography_array, artist_discography); //Adiciona o respetivo elemento ao array dentro do catálogo
}



void transform_into_sorted_discography_array (ArtistsCatalog* catalog){

    GHashTable *artist_table = get_artists(catalog);
    
    /*
    g_hash_table_foreach é uma função da GLib que aplica uma função dada por nós a cada elemento da hashtable, neste caso quero
    ir a cada artista, copiar informções que pretendo e armazenar em um array
    */
    g_hash_table_foreach(artist_table,add_to_artist_discography_array,catalog);

    //Ordena inversamente o array criado anteriormente
    g_ptr_array_sort(catalog->sorted_discography_array,compare_artist_discography_desc);

}

ArtistsCatalog *create_artist_catalog() {
    ArtistsCatalog *catalog = g_malloc(sizeof(ArtistsCatalog));
    
    catalog->artists = g_hash_table_new_full(g_int_hash, g_int_equal, g_free, (GDestroyNotify)free_artist); //Estrutura "base" de artistas
    
    catalog->sorted_discography_array = g_ptr_array_new_with_free_func((GDestroyNotify)free_artist_discography); //Estrutura auxiliar para querie 2

    return catalog;
} 


void free_artists_catalog(ArtistsCatalog* catalog ) {
    g_hash_table_destroy(catalog->artists);
    
    g_ptr_array_free(catalog->sorted_discography_array,TRUE);

    free(catalog);
};

void insert_to_artists_catalog (ArtistsCatalog* catalog,Artist* artist){
    int* key =g_new(int, 1);
    *key = get_artist_id(artist);
    g_hash_table_insert(catalog->artists,key,artist);
}

Artist *get_artist_by_id(ArtistsCatalog* catalog, int id){
    int* key = g_new(int, 1);
    *key = id;       // Allocate memory for one integer 
    Artist* artist = g_hash_table_lookup(catalog->artists,key);
    g_free(key);
    return artist;
}

GHashTable* get_artists (ArtistsCatalog* catalog){
    return catalog->artists;
}


GPtrArray* get_artist_dicography_array(ArtistsCatalog* catalog){
    return catalog->sorted_discography_array;
}


gboolean valid_artist_id (ArtistsCatalog* artistCatalog,int id){
    int *key = g_new(int,1);
    *key = id;
    gboolean is_valid = g_hash_table_contains(get_artists(artistCatalog),key);
    g_free(key);
    return is_valid;
}


int valid_artist(GArray *artist_ids, ArtistsCatalog* catalog){

    
    for(guint index = 0; index < artist_ids->len; index++){

        if(!valid_artist_id(catalog,g_array_index(artist_ids,int,index)))
            return 0;
    }


    return 1;
}


ArtistDiscography** top_N_artists(ArtistsCatalog* catalog, char* n_artists, char* country) {
    
    // Get the sorted artist discography array
    GPtrArray* artist_sorted_discography = get_artist_dicography_array(catalog);

    // Convert the number of artists from string to integer
    guint num = (guint)atoi(n_artists); 

    // Allocate space for the output list
    ArtistDiscography** top_n_list = malloc(sizeof(ArtistDiscography*) * num);
    if (!top_n_list) return NULL; // Handle memory allocation failure
    guint i = 0;
    if (country == NULL) {
        // No country filter - pick the top N artists directly
        for (i = 0; i < num && i < artist_sorted_discography->len; i++) {
            ArtistDiscography* artist = g_ptr_array_index(artist_sorted_discography, i);
            top_n_list[i] = artist; // Add to the list
        }
        //Verify if the number of artists is less than the number of artists requested
        if (i >= artist_sorted_discography->len) {
            for (guint k = i; k < num; k++) {
                top_n_list[k] = NULL; // Fill the rest of the list with NULL
            }
        }
    } else {
        // Filter by country
        guint j = 0; // Use a separate index to add matching artists
        for (i = 0; j < num && i < artist_sorted_discography->len; i++) {
            ArtistDiscography* artist = g_ptr_array_index(artist_sorted_discography, i);
            char* artist_country = get_artist_discography_country(artist);

            if (!strcmp(artist_country, country)) { // Check country match
                top_n_list[j++] = artist; // Add to the list
            }

            free(artist_country);
        }
        //Verify if we actually found the number of artists requested or not
        if (j < num){
            for (guint k = j; k < num; k++) {
                top_n_list[k] = NULL; // Fill the rest of the list with NULL
            }
        }
    }

    return top_n_list;
}


float calculate_recipe(ArtistsCatalog* catalog, Artist* artist){
    float recipe = calculate_artist_recipe(artist);
    if (!is_group(artist)) {
        int len = group_participation_lenght(artist);
        for (int i = 0; i < len; i++) {
            Artist* colective_artist = get_artist_by_id(catalog, get_group_participation_index(artist, i));
            recipe += calculate_recipe(catalog, colective_artist) / get_number_of_artist_constituents(colective_artist);
        }
    }
    return recipe;
}


GList* get_keys_for_iterating_artists(ArtistsCatalog* catalog){
    return g_hash_table_get_keys(catalog->artists);
}

void actualize_artist_group_participation(ArtistsCatalog* catalog){
    GList * keys = get_keys_for_iterating_artists(catalog);
    GList * iterator = keys;

    while (iterator != NULL) {
        Artist* current_artist = get_artist_by_id(catalog, *(int*)iterator->data);
        if (is_group(current_artist)) {
            GArray * artist_ids = get_artist_id_constituent(current_artist);
            for (guint i = 0; i < artist_ids->len; i++)
                add_to_group_participation(get_artist_by_id(catalog, g_array_index(artist_ids, int, i)), get_artist_id(current_artist));
            g_array_free(artist_ids, TRUE); 
        }
        iterator = iterator->next;
    }

    g_list_free(keys);
}