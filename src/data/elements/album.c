#include "./data/elements/album.h"
#include <stdio.h>

typedef struct album{
    int id;
    char* title;
    GArray* artist_id;
    char* year;
    GArray* producers_list;
} Album;


Album* create_album(char* id, char* title, GArray* artist_id, char* year, GArray* producers_list) {
    
    Album* album_instance = initialize_album();
    

    album_instance->id = atoi(id+2);
    album_instance->title = strdup(title);
    album_instance->artist_id = artist_id;
    album_instance->year = strdup(year);
    album_instance->producers_list = producers_list;

    return album_instance;
}

Album* initialize_album(){
    Album* album_instance = malloc(sizeof(struct album));

    album_instance->title = NULL;
    album_instance->artist_id = NULL;
    album_instance->year = NULL;
    album_instance->producers_list = NULL;

    return album_instance;
}

void free_album(Album* album){
    free(album->title);
    g_array_free(album->artist_id, TRUE);
    free(album->year);
    g_array_free(album->producers_list, TRUE);
    free(album);
}

int get_album_id(Album* album) {
    return album->id;
}

void set_album_id(Album* album, int id) {
    album->id = id;
}

char* get_album_title(Album* album) {
    return strdup(album->title);
}

void set_album_title(Album* album, char* title){
    album->title = strdup(title);
}

GArray* get_album_artist_id(Album* album) {
    return g_array_copy(album->artist_id);
}

void set_album_artist_id(Album* album, GArray* artist_id) {
    album->artist_id = artist_id;
}

char* get_album_year(Album* album) {
    return strdup(album->year);
}

void set_album_year(Album* album, char* year){
    album->year = strdup(year);
}

GArray* get_album_producers_list(Album* album) {
    return g_array_copy(album->producers_list);
}

void set_album_producers_list(Album* album, GArray* producers_list){
    album->producers_list = producers_list;
}