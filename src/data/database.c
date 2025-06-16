#include "./data/database.h"
#include "./file_workers/parser.h"
#include "./data/catalogs/catalogs_utils/parse_utils.h"
#include "./data/catalogs/catalogs_utils/populate_genre_musics_catalog.h"
#include "./file_workers/parser.h"
#include "./utils/format.h"
#include "./data/catalogs/catalogs_utils/determine_top_10.h"

#include <stdio.h>

typedef struct database{

    UsersCatalog* users_catalog;
    ArtistsCatalog* artists_catalog;
    MusicsCatalog* musics_catalog;
    HistorysCatalog* historys_catalog;
    AlbumCatalog* album_catalog;

}DataBase;

DataBase* initialize_database(){

    DataBase* database = malloc(sizeof(DataBase));

    database->users_catalog = create_users_catalog();
    database->artists_catalog = create_artist_catalog();
    database->musics_catalog = create_music_catalog();
    
    database->historys_catalog = create_historys_catalog();
    database->album_catalog = create_album_catalog();

    return database;

}

void free_database(DataBase* database){

    free_users_catalog(database->users_catalog);

    free_artists_catalog(database->artists_catalog);

    free_musics_catalog(database->musics_catalog);

    free_historys_catalog(database->historys_catalog);

    free_album_catalog(database->album_catalog);

    free(database);

}

UsersCatalog* get_users_catalog(DataBase* database){

    return database->users_catalog;

} 

ArtistsCatalog* get_artists_catalog(DataBase* database){

    return database->artists_catalog;

} 

MusicsCatalog* get_musics_catalog(DataBase* database){

    return database->musics_catalog;

} 

AlbumCatalog* get_albums_catalog(DataBase* database){

    return database->album_catalog;

}

HistorysCatalog* get_historys_catalog(DataBase* database){

    return database->historys_catalog;

}

Recommender* get_recommender(DataBase* database){
    return get_catalog_recommender(get_users_catalog(database));
}

typedef struct data_pair{
    DataBase* database;
    Recommender* recommender;
} DataPair;


void populate_recommender(gpointer key, gpointer value, gpointer user_data){
    GPtrArray* history_list = (GPtrArray*)value;
    int user_id = *(int*)key;
    char* user_id_string = format_user_id(user_id);
    DataPair* data = (DataPair*)user_data;
    add_user_to_recommender(data->recommender, user_id_string);
    free(user_id_string);

    for (guint i = 0; i < history_list->len; i++) {
        History* history = g_ptr_array_index(history_list, i);

        char* genre = get_music_genre(get_music_by_id(get_musics_catalog(data->database), get_history_music_id(history)));
        add_like_to_recommender(data->recommender, genre);
        free(genre);
    }
    increment_user_count(data->recommender);
}

Recommender* create_and_populate_recommender(HistorysCatalog* historyCatalog,int nUsers, int nGenres,DataBase* database){
    DataPair* data = malloc(sizeof(DataPair));
    Recommender* recommender = create_recommender(nUsers, nGenres);
    data->database = database;
    data->recommender = recommender;
    g_hash_table_foreach(get_historybyuser(historyCatalog), populate_recommender, data);
    free(data);
    return recommender;
}


int populate_database(DataBase* database, char* path_to, int test) {
    printf("\n=========================================\n");
    printf("       STARTING DATABASE POPULATION   \n");
    printf(  "=========================================\n\n");

    int path_len = strlen(path_to);

    printf("🔄 Starting to populate: ARTISTS\n");

    char* path_to_artists = malloc(path_len + 20);
    sprintf(path_to_artists, "%s/artists.csv", path_to);

    printf("📂 File Path: %s\n", path_to_artists);

    parser(database, path_to_artists,validate_and_add);

    free(path_to_artists);
    printf("✅ Finished populating: ARTISTS\n\n");


    printf("🔄 Starting to populate: ALBUMS\n");
    
    char* path_to_albums = malloc(path_len + 20);
    sprintf(path_to_albums, "%s/albums.csv", path_to);

    printf("📂 File Path: %s\n", path_to_albums);

    parser(database, path_to_albums, validate_and_add);

    printf("✅ Finished populating: ALBUMS\n\n");
    free(path_to_albums);


    printf("🔄 Starting to populate: MUSICS\n");

    char* path_to_musics = malloc(path_len + 20);
    sprintf(path_to_musics, "%s/musics.csv", path_to);

    printf("📂 File Path: %s\n", path_to_musics);

    parser(database, path_to_musics, validate_and_add);

    free(path_to_musics);
    printf("✅ Finished populating: MUSICS\n\n");

    printf("🔄 Starting to populate: USERS\n");

    char* path_to_users = malloc(path_len + 20);
    sprintf(path_to_users, "%s/users.csv", path_to);

    printf("📂 File Path: %s\n", path_to_users);

    int user_Count = parser(database, path_to_users, validate_and_add);

    free(path_to_users);
    printf("✅ Finished populating: USERS\n\n");

    printf("🔄 Starting to populate: HISTORY\n");

    char* path_to_history = malloc(path_len + 20);
    sprintf(path_to_history, "%s/history.csv", path_to);

    printf("📂 File Path: %s\n", path_to_history);

    parser(database, path_to_history, validate_and_add);

    free(path_to_history);

    printf("✅ Finished populating: HISTORY\n\n");

    if (!test) {
        printf("🔧 Performing additional data transformations...\n");

        transform_into_sorted_discography_array(get_artists_catalog(database));
        populate_genre_musics_catalog(database);
        actualize_artist_group_participation(get_artists_catalog(database));
        
        Recommender* recommender = create_and_populate_recommender(get_historys_catalog(database),user_Count, get_genres_count(get_musics_catalog(database)),database);
        set_recommender(get_users_catalog(database),recommender);
        
        calculate_top_10_per_week(get_historys_catalog(database));
        
        printf("🔧 Data transformations complete.\n\n");
    }

    printf("=========================================\n");
    printf("        DATABASE POPULATION COMPLETE     \n");
    printf("=========================================\n\n");
    return user_Count;
}
