#include "./data/elements/artist.h"
#include "./utils/float_conversion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct artist {
    int id;
    char* name;
    float recipe_per_stream;
    GArray* id_constituent;
    char* country;
    short int type; // 0 - individual, 1 - group
    int music_reproductions; //Útil para querie 1
    int individual_artist_albuns; //Útil para querie 1
    GArray* groups_participation; //Útil para querie 1
    int discography; //Útil para querie 2
    int times_on_top_10; //Útil para querie 4
} Artist;


void initialize_group_participation(Artist* artist){
    artist->groups_participation = g_array_new(TRUE, FALSE, sizeof(int));
}

Artist* create_artist(char* id, char* name, char* recipe_per_stream, GArray* id_constituent, char* country,char* type) {
    
    Artist* artist_instance = initialize_artist();

    artist_instance->id = atoi(id+1);
    artist_instance->name = strdup(name);
    convert_string_to_float(recipe_per_stream, &artist_instance->recipe_per_stream);
    artist_instance->id_constituent = id_constituent;
    artist_instance->country = strdup(country);
    set_artist_type(artist_instance,type);
    artist_instance->music_reproductions = 0;
    artist_instance->individual_artist_albuns = 0;
    initialize_group_participation(artist_instance);
    artist_instance->discography = 0;
    artist_instance->times_on_top_10 = 0;

    return artist_instance;
}

Artist* initialize_artist() {
    Artist* artist_instance = malloc(sizeof(struct artist));

    artist_instance->name = NULL;
    artist_instance->id_constituent = NULL;
    artist_instance->country = NULL;
    artist_instance->groups_participation = NULL;

    return artist_instance;
}

void free_artist(Artist* artist){

    free(artist->name);
    g_array_free(artist->id_constituent, TRUE);
    free(artist->country);
    g_array_free(artist->groups_participation, TRUE);
    free(artist);
}


int get_artist_id(Artist* artist) {
    return artist->id;
}

void set_artist_id(Artist* artist, int id) {
    artist->id = id;
}

char* get_artist_name(Artist* artist) {
    return strdup(artist->name);
}

void set_artist_name(Artist* artist, char* name) {
    artist->name = strdup(name);
}

int get_artist_recipe_per_stream(Artist* artist) {
    return artist->recipe_per_stream;
}

void set_artist_recipe_per_stream(Artist* artist, int recipe_per_stream) {
    artist->recipe_per_stream = recipe_per_stream;
}

int* copy_int(const int* src) {
    int* dest = g_malloc(sizeof(int));
    *dest = *src;
    return dest;
}

GArray* get_artist_id_constituent(Artist* artist) {
    return g_array_copy(artist->id_constituent);
}

void set_artist_id_constituent(Artist* artist,GArray* id_constituent){
    artist->id_constituent = id_constituent;
}

char* get_artist_country(Artist* artist) {
    return strdup(artist->country);
}

void set_artist_country(Artist* artist, char* country) {
    artist->country = strdup(country);
}

short int get_artist_type(Artist* artist) {
    return artist->type;
}

void set_artist_type(Artist* artist, char* type) {
    if (!strcmp(type,"individual"))
        artist->type = 0;

    else if (!strcmp(type,"group"))
        artist->type = 1;
}

void add_to_artist_discography(Artist* artist,int duration){
    artist->discography += duration;
}

int get_artist_discography(Artist* artist){
    return artist->discography;
}

int is_group(Artist* artist){
    return artist->type;
}

int get_number_of_individual_albums(Artist* artist){
    return artist->individual_artist_albuns;
}

int get_number_of_artist_constituents(Artist* artist){
    return artist->id_constituent->len;
}

int get_music_reproductions (Artist* artist) {
    return artist->music_reproductions;
}

void increment_individual_artist_albuns(Artist* artist){
    artist->individual_artist_albuns++;
}

void increment_music_reproductions(Artist* artist){
    artist->music_reproductions++;
}

float calculate_artist_recipe(Artist* artist){
    return artist->recipe_per_stream * artist->music_reproductions;
}

int group_participation_lenght(Artist* artist){
    return artist->groups_participation->len;
}

int get_group_participation_index(Artist* artist, int index){
    return g_array_index(artist->groups_participation, int, index);
}

void add_to_group_participation(Artist* artist, int group_id){
    for (guint i = 0; i < artist->groups_participation->len; i++) {
        if (g_array_index(artist->groups_participation, int, i) == group_id) {
            return;
        }
    }
    g_array_append_val(artist->groups_participation, group_id);
}

void increment_times_on_top_10(Artist* artist){
    artist->times_on_top_10++;
}

int get_times_on_top_10(Artist* artist){
    return artist->times_on_top_10;
}

void reset_times_on_top_10(Artist* artist){
    artist->times_on_top_10 = 0;
}