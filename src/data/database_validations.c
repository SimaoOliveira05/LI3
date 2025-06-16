#include "./data/catalogs/musics_catalog.h"
#include "./data/catalogs/artists_catalog.h"
#include "./data/catalogs/album_catalog.h"
#include "./data/catalogs/historys_catalog.h"
#include "./data/catalogs/users_catalog.h"
#include "./utils/validations.h" 
#include "./utils/time.h"
#include "./data/catalogs/catalogs_utils/parse_utils.h"
#include "./data/database_validations.h"
#include "./file_workers/writer.h"

int validate_and_add_music(char** tokens, MusicsCatalog* musicCatalog, ArtistsCatalog* artistsCatalog, AlbumCatalog* albumCatalog) {
    char* token2 = strdup(tokens[2]);
    GArray* artist_ids = format_ids_list(token2);
    free(token2);

    int id = atoi(tokens[3]+2);

    if (!valid_artist(artist_ids, artistsCatalog) || time_validation(tokens[4]) || !get_album_by_id(albumCatalog, id)) {
        g_array_free(artist_ids, TRUE);
        return 1;
    }


    Music* music = create_music(tokens[0],             //id
                                    artist_ids,   //Lista de ids do artistas constituintes
                                    tokens[4],         //Duração 
                                    tokens[3],        //Album id
                                    tokens[6],         //Year
                                    tokens[1],         //Title
                                    tokens[5]          // Genre
                                    );       
    
    add_music_duration_to_artist_list(artist_ids,artistsCatalog,convert_time_to_seconds(tokens[4]));
    
    insert_to_musics_catalog(musicCatalog, music);

    verify_or_add_genre(musicCatalog, tokens[5]);

    return 0;
}


int validate_and_add_user(char** tokens, UsersCatalog* usersCatalog, MusicsCatalog* musicsCatalog,HistorysCatalog* historyCatalog) {
    char* token7 = strdup(tokens[7]);
    GArray* liked_musics_ids = format_ids_list(token7);
    free(token7);



    if (!valid_musics(liked_musics_ids, musicsCatalog) || 
        email_validation(tokens[1]) || 
        date_validation(tokens[4]) || 
        !subscription_type_validation(tokens[6])) { 
        
        g_array_free(liked_musics_ids, TRUE);
        return 1;
    }


    User* user = create_user(tokens[0],
                             tokens[1],
                             tokens[2],
                             tokens[3],
                             tokens[4],
                             tokens[5],
                             tokens[6],
                             liked_musics_ids);

    insert_to_users_catalog(usersCatalog, user);

    insert_user_to_history_table(historyCatalog, get_user_username(user));

    return 0;
}

int validate_and_add_artist(char** tokens,ArtistsCatalog* artistCatalog){
    
    if (!artist_id_validation(tokens[4],tokens[6]) || !type_validation(tokens[6]))
                return 1;
    
    char* token4 = strdup(tokens[4]);
    GArray* id_constituent = format_ids_list(token4);
    free(token4);


    Artist* artist = create_artist( tokens[0],
                                    tokens[1],
                                    tokens[3],
                                    id_constituent,
                                    tokens[5],
                                    tokens[6]);

    insert_to_artists_catalog(artistCatalog,artist);

    return 0;
}


int validate_and_add_history(char** tokens, ArtistsCatalog* artistsCatalog, MusicsCatalog* musicsCatalog, HistorysCatalog* historyCatalog) {
    
    char date[11];
    get_date(tokens[3],date);

    char time[9];
    get_time(tokens[3],time);
    
    
    if (time_validation(tokens[4]) || !platform_validation(tokens[5])){
        return 1;
    }
    
    int duration = convert_time_to_seconds(tokens[4]);
    History* history = create_history(tokens[1],tokens[2],date,time,duration,tokens[5]);

    //Actualize the artist informations in the catalog for query 1 and query 4 purposes

    int id = atoi(tokens[2]+1);
    
    GArray* artist_ids = get_music_artist_id(get_music_by_id(musicsCatalog, id));
    for (guint i = 0; i < artist_ids->len; i++) {
        Artist* artist = get_artist_by_id(artistsCatalog, g_array_index(artist_ids,int, i)); 
        increment_music_reproductions(artist);

        int week_offset = get_week_offset(date);
        actualize_artistDurationTree(historyCatalog, week_offset, get_artist_id(artist), duration);
        
        //add_to_user_country_recommender(get_user_by_id(usersCatalog, get_history_user_id(history)), get_artist_country(artist), duration);
    }
    
    g_array_free(artist_ids, TRUE);

    insert_to_historys_catalog(historyCatalog, history);

    //add_to_user_genre_recomemender(get_user_by_id(usersCatalog, get_history_user_id(history)), get_music_genre(get_music_by_id(musicsCatalog, id)), duration);

    //add_to_user_music_recommender(get_user_by_id(usersCatalog, get_history_user_id(history)), id, duration);
    
    return 0;
}


int add_album(char** tokens, AlbumCatalog* albumsCatalog, ArtistsCatalog* artistsCatalog) {

    char* token2 = strdup(tokens[2]);
    GArray* artist_id = format_ids_list(token2);
    free(token2);

    char* token4 = strdup(tokens[4]);
    GArray* producers_list = format_ids_list(token4);
    free(token4);


    Album* album = create_album(tokens[0], tokens[1], artist_id, tokens[3], producers_list);


    for (guint i = 0; i < artist_id->len; i++){
        Artist* artist = get_artist_by_id(artistsCatalog, g_array_index(artist_id,int, i));
        increment_individual_artist_albuns(artist);
    }


    insert_to_album_catalog(albumsCatalog, album);

    return 0;
}

StructType detectType (char* line){
    if (line[0] == 'A' && line[1] == 'L') return ALBUM; 
    if (line[0] == 'A') return ARTIST;
    if (line[0] == 'U') return USER;
    if (line[0] == 'S') return MUSIC;
    if (line[0] == 'H') return HISTORY;
    return 0;
}


StructType detectTypeHeader (char* token){
    if (token[6] == 'n') return ARTIST;
    if (token[1] == 'u') return USER;
    if (token[26] == 'a') return MUSIC;
    if (token[6] == 'u') return HISTORY;
    if (token[26] == 'y') return ALBUM;
    return 0;
}


int validate_and_add (char** tokens, void* database, char* line){

    
    database = (DataBase*) database;

    StructType type;

    //Case the line is a header
    if (strcmp(line, "\"id\";\"name\";\"description\";\"recipe_per_stream\";\"id_constituent\";\"country\";\"type\"\n") == 0 ||
        strcmp(line, "\"id\";\"title\";\"artist_id\";\"album_id\";\"duration\";\"genre\";\"year\";\"lyrics\"\n") == 0 ||
        strcmp(line, "\"username\";\"email\";\"first_name\";\"last_name\";\"birth_date\";\"country\";\"subscription_type\";\"liked_songs_id\"\n") == 0 ||
        strcmp(line, "\"id\";\"user_id\";\"music_id\";\"timestamp\";\"duration\";\"platform\"\n") == 0 ||
        strcmp(line, "\"id\";\"title\";\"artist_id\";\"year\";\"producers\"\n") == 0) {
            type = detectTypeHeader(line);
        write_error(type, line);
        return 0;
    }

    type = detectType(tokens[0]);
    
    switch (type) {
        case MUSIC:
        
            if(validate_and_add_music(tokens,get_musics_catalog(database),get_artists_catalog(database),get_albums_catalog(database))){
                write_error(type, line);
                return 1;
            }
            break;

        case USER:
            
            if (validate_and_add_user(tokens,get_users_catalog(database),get_musics_catalog(database),get_historys_catalog(database))){
                write_error(type, line);
                return 1;
            }
            break;

        case ARTIST:

            if(validate_and_add_artist(tokens,get_artists_catalog(database))){
                write_error(type, line);
                return 1;
            }
            break;
        
        case HISTORY:
            
            if (validate_and_add_history(tokens,get_artists_catalog(database), get_musics_catalog(database), get_historys_catalog(database))){
                    write_error(type, line);
                    return 1;
            }
            break;


        case ALBUM:

            if(add_album(tokens,get_albums_catalog(database), get_artists_catalog(database))){
                write_error(type, line);
                return 1;
            }
            break;
            
    }
    return 0;
}