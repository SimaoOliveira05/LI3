#include "./data/catalogs/users_catalog.h"
#include "./utils/validations.h"
#include "./utils/validations.h"

typedef struct usersCatalog {
    GHashTable *users;
    Recommender *recommender;
} UsersCatalog;




UsersCatalog* create_users_catalog(){
    UsersCatalog* catalog = g_malloc(sizeof(UsersCatalog));
    catalog->users = g_hash_table_new_full(g_int_hash, g_int_equal, g_free, (GDestroyNotify)free_user);
    catalog->recommender = NULL;
    return catalog;
}

void free_users_catalog(UsersCatalog* catalog) {
    g_hash_table_destroy(catalog->users);
    free_recommender(catalog->recommender);
    free(catalog);
}

void insert_to_users_catalog(UsersCatalog* catalog, User* user) {
    int* key =g_new(int, 1);
    *key = get_user_username(user);
    g_hash_table_insert(catalog->users, key, user);
}

User* get_user_by_id(UsersCatalog* catalog, int id) {
    int* key =g_new(int, 1);
    *key = id;
    User* user= g_hash_table_lookup(catalog->users, key);
    g_free(key);
    return user;
}

GHashTable* get_users (UsersCatalog* catalog){
    return catalog->users;
}

Recommender* get_catalog_recommender(UsersCatalog* catalog){
    return catalog->recommender;
}

void set_recommender(UsersCatalog *catalog, Recommender* recommender){
    catalog->recommender = recommender;
}



