#include "./data/elements/music.h"

typedef struct music{
    int id;
    GArray *artist_ids; 
    int duration; 
    short unsigned int year;
    int album_id;
    char* title;
    char* genre;
} Music;


Music* create_music(char* id, GArray* artist_ids,char* duration, char* album_id, char* year,
                                     char* title, char* genre){
                        
    Music* music_instance = initialize_music();

    music_instance->artist_ids = artist_ids;
    music_instance->id = atoi (id+1);
    music_instance->year=atoi(year);
    music_instance->album_id = atoi(album_id+2);
    music_instance->duration = atoi(duration);
    music_instance->genre = strdup(genre);
    music_instance->title = strdup(title);

    return music_instance;
}


Music* initialize_music(){

    Music* music_instance = malloc(sizeof(struct music));

    music_instance->title = NULL;
    music_instance->genre = NULL;
    music_instance-> artist_ids = NULL; //Mudei a parse ids list e agora ela própria cria a lista

    return music_instance;
}


void free_music(Music* music){
    
    //função de free de glib
    g_array_free(music->artist_ids,TRUE); //Função que dá free ao array de pointer da glib, o "TRUE" significa que deve tambem dar free aos seus elementos (pois são strings)
    free(music->title);
    free(music->genre);
    free(music);
}

int get_number_of_artists(Music* music) {
    return music->artist_ids->len;
}

int get_music_id(Music* music){
    return music->id;
}

void set_music_id(Music* music, int id){
    music->id = id;
}




GArray* get_music_artist_id(Music* music) {
    return g_array_copy(music->artist_ids);
}


void set_music_artist_id(Music* music, GArray* artist_id_list){
    music->artist_ids = artist_id_list;
}


int get_music_duration (Music* music){
    return music->duration;
}

void set_music_duration (Music* music, int time){
    music->duration=time;
}


short unsigned int get_music_year (Music* music){
    return music->year;
}

void set_music_year (Music* music,short unsigned int year){
    music->year = year;
}

char* get_music_title(Music* music){
    return strdup(music->title);
}

void set_music_title(Music* music,char* title){
    music->title = strdup(title);
}


char* get_music_genre(Music* music){
    return strdup(music->genre);
}

void set_music_genre(Music* music,char* genre){
    music->genre = strdup(genre);
}

int get_music_album_id(Music* music){
    return music->album_id;
}

void set_music_album_id(Music* music,int album_id){
    music->album_id = album_id;
}