#include "./data/catalogs/album_catalog.h"

typedef struct albumCatalog {
    GHashTable *albums;
} AlbumCatalog;

AlbumCatalog* create_album_catalog(){
    AlbumCatalog* catalog = g_malloc(sizeof(AlbumCatalog));
    catalog->albums = g_hash_table_new_full(g_int_hash, g_int_equal, g_free, (GDestroyNotify)free_album);
    return catalog;
}

void free_album_catalog(AlbumCatalog* catalog){
    g_hash_table_destroy(catalog->albums);
    g_free(catalog);
}

void insert_to_album_catalog(AlbumCatalog* catalog, Album* album) {
    int* key =g_new(int, 1);
    *key = get_album_id(album);
    g_hash_table_insert(catalog->albums, key, album);
}

Album* get_album_by_id(AlbumCatalog* catalog, int id) {

    int* key =g_new(int, 1);
    *key = id;
    Album* album = g_hash_table_lookup(catalog->albums, key);
    g_free(key);
    return album;
}

GHashTable* get_albums(AlbumCatalog* catalog){
    return catalog->albums;
}

