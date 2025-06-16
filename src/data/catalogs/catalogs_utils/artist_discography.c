#include "./data/catalogs/catalogs_utils/artist_discography.h"
#include <stdlib.h>
#include <glib.h>


typedef struct artist_discography{
    int id;
    char* name;
    short int type;
    int discography;
    char* country;
} ArtistDiscography;

ArtistDiscography* create_artist_discography(int id,char* name,short int type,int discography,char* country){

    ArtistDiscography* artist_discography_instance = inicialize_artist_discography();

    artist_discography_instance->id = id;
    artist_discography_instance->name = strdup(name);
    artist_discography_instance->type = type;
    artist_discography_instance->discography = discography;
    artist_discography_instance->country = strdup(country);
    
    return artist_discography_instance;
}


ArtistDiscography* inicialize_artist_discography(){
     ArtistDiscography* artist_discography_instance = malloc(sizeof(ArtistDiscography));

     artist_discography_instance-> name = NULL;
     artist_discography_instance->country = NULL;

     return artist_discography_instance;
}


void free_artist_discography(ArtistDiscography* artist_discography){

    free(artist_discography->name);
    free(artist_discography->country);
    free(artist_discography);
}


char* get_artist_discography_name (ArtistDiscography* artist){
    return strdup(artist->name);
}

char* get_artist_discography_country (ArtistDiscography* artist){
    return strdup(artist->country);
}

int get_artist_discography_discography (ArtistDiscography* artist){
    return artist->discography;
    }

int get_artist_discography_type (ArtistDiscography* artist){
    return artist->type;
    }

gint compare_artist_discography_desc(const void* a, const void* b) {
    const ArtistDiscography* artist_a = *(const ArtistDiscography**)a;
    const ArtistDiscography* artist_b = *(const ArtistDiscography**)b;
    if (artist_b->discography - artist_a->discography == 0)
        return artist_a->id - artist_b->id;
    
    return artist_b->discography - artist_a->discography;
}