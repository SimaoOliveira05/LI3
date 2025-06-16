#include "./data/catalogs/catalogs_utils/populate_genre_musics_catalog.h"
#include "./utils/age.h"

void populate_genre_musics_catalog(DataBase* db) {
    // Get the keys and create an iterator
    GList * keys = g_hash_table_get_keys(get_users(get_users_catalog(db)));
    GList * iterator = keys;

    // Get the genres hash table
    MusicsCatalog* musics_catalog = get_musics_catalog(db);
    
    // Iterate over the users
    while (iterator != NULL) {

        // Get the user's liked music and age 
        User * user = get_user_by_id(get_users_catalog(db), *(int*)iterator->data);
        GArray *music = get_user_liked_music_id(user);
        int music_size = get_user_liked_music_size(user);
        int age = calculate_age(get_user_birth_date(user));

        // Iterate over the liked music
        for (int i = 0; i < music_size; i++) {
            // Get the music genre
            int music_id = g_array_index(music,int, i);
            char *genre = get_music_genre(get_music_by_id(get_musics_catalog(db), music_id));

            // If the genre is not in the catalog, insert it. Update the genre catalog.
            if (!search_on_genres_music_catalog(musics_catalog, genre))
                insert_to_genres_music_catalog(musics_catalog, genre);
            update_genres_music_catalog(musics_catalog, genre, age);
        }
        
        //Free the music array
        g_array_free(music, TRUE);

        // Update the iterator
        iterator = iterator->next;
    }

    // Free
    g_list_free(keys);
}

