#include "./data/elements/history.h"
#include "./data/catalogs/historys_catalog.h"
#include "./data/catalogs/catalogs_utils/determine_top_10.h"
#include "./utils/time.h"
#include "./utils/validations.h"
#include "./utils/cmp.h"

typedef struct historysCatalog {
    GHashTable *historysByUser; //Keys are user ids, values are GPtrArrays of History pointers
    Top10Struct *top10Struct;
} HistorysCatalog;

HistorysCatalog* create_historys_catalog(){
    HistorysCatalog* catalog = g_malloc(sizeof(HistorysCatalog));
    catalog->historysByUser = g_hash_table_new_full(g_int_hash, g_int_equal, g_free, (GDestroyNotify)g_ptr_array_unref);
    catalog->top10Struct = create_top10_struct();

    return catalog;
}

void free_historys_catalog(HistorysCatalog* catalog){
    g_hash_table_destroy(catalog->historysByUser);
    free_top10_struct(catalog->top10Struct);
    free(catalog);
}

GHashTable* get_historybyuser(HistorysCatalog* catalog){
    return catalog->historysByUser;
}

void insert_to_historys_catalog(HistorysCatalog* catalog, History* history){
    
    char year[5];
    char* date = get_history_date(history);
    
    int userId = get_history_user_id(history);
    int *key = g_new(int,1);
    *key = userId;
    
    get_year(date,year);
    free(date);

    GPtrArray* historyListByUser = g_hash_table_lookup(catalog->historysByUser, key);
    

    if (historyListByUser == NULL) {
        historyListByUser = g_ptr_array_new_with_free_func((GDestroyNotify)free_history);
        g_hash_table_insert(catalog->historysByUser, key, historyListByUser);
    }
    else {
        g_free(key);
    }
    
    g_ptr_array_add(historyListByUser, history);
}

GPtrArray* get_history_list_by_user(HistorysCatalog* catalog, int user_id){
    int* key = g_new(int,1);
    *key = user_id;
    GPtrArray* historyList = g_hash_table_lookup(catalog->historysByUser, key);
    free(key);
    return historyList; 
}

GHashTable* get_history_by_user(HistorysCatalog* catalog){
    return catalog->historysByUser;
}

void insert_user_to_history_table(HistorysCatalog* catalog, int user_id){
    int* key = g_new(int,1);
    *key = user_id;
    int* exists = g_hash_table_lookup(catalog->historysByUser, key);
    if (exists == NULL)
        g_hash_table_insert(catalog->historysByUser, key, g_ptr_array_new_with_free_func((GDestroyNotify)free_history));
}


int verify_if_user_exists(HistorysCatalog* catalog, int user_id){
    int* key = g_new(int,1);
    *key = user_id;
    int* exists = g_hash_table_lookup(catalog->historysByUser, key);
    if (exists == NULL){
        free(key);
        return 0;
    }
    free(key);
    return 1;
}


//Top 10 functions

int* get_top_10_by_week(HistorysCatalog* catalog, int week_offset){
    return get_top_10_by_week_from_top10(catalog->top10Struct, week_offset);
}

void actualize_artistDurationTree(HistorysCatalog* catalog, int week_offset, int artist_id, int duration) {
    add_to_artistDurationTree_struct_from_top10(catalog->top10Struct, week_offset, artist_id, duration);
}

void determine_artist_top_10(HistorysCatalog* catalog, int week_offset) {

    int top10_duration[10] = {0};
    int *top10_ids;
    top10_ids = get_top_10_by_week_from_top10(catalog->top10Struct, week_offset);  

    // Get the first node of the tree
    GTree* artistDurationTree = get_artistDurationTree_by_week(catalog->top10Struct, week_offset);
    GTreeNode* node = g_tree_node_first(artistDurationTree);

    // Iterate over the tree
    while (node != NULL) {

        // Get the key and value of the node
        int *artist_id = (int*)g_tree_node_key(node);
        int *duration = (int*)g_tree_node_value(node);
        //printf("artist_id: %d, duration: %d\n", *artist_id, *duration);


        // Insert ordenly the artist in the top 10 if it has a higher duration
        int i;
        for (i = 9; i >= 0; i--) {
 
            if (*duration > top10_duration[i] || (*duration == top10_duration[i] && *artist_id < top10_ids[i])) {
                if (i < 9) {
                    top10_ids[i + 1] = top10_ids[i];
                    top10_duration[i + 1] = top10_duration[i];
                }
                top10_ids[i] = *artist_id;
                top10_duration[i] = *duration;
            } else {
                break;
            }
        }

        // Move to the next node
        node = g_tree_node_next(node);
    }
}

void calculate_top_10_per_week(HistorysCatalog* catalog) {

    // Get the keys of the historys catalog
    GList* keys = get_weeks_with_history(catalog->top10Struct);
    GList* iter = keys;

    while (iter != NULL) {
        int week_offset = *(int*)iter->data;
        determine_artist_top_10(catalog, week_offset);

        actualize_min_and_max_week_offset(catalog->top10Struct, week_offset);

        iter = g_list_next(iter);
    }

    g_list_free(keys);
}

void get_min_and_max_week_offset(HistorysCatalog* catalog, int* min_week_offset, int* max_week_offset) {
    get_min_and_max_week_offset_from_top10(catalog->top10Struct, min_week_offset, max_week_offset);
}