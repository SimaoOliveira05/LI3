#include "./data/catalogs/catalogs_utils/determine_top_10.h"
#include "./utils/cmp.h"
#include "./utils/time.h"
#include <unistd.h>

typedef struct top10PerWeek {
    GTree *artistDurationTree;
    int top10[10];
} Top10PerWeek;

typedef struct top10Struct{
    int min_week_offset;
    int max_week_offset;
    GHashTable *top10Table;
} Top10Struct;

void free_top10_struct(gpointer data) {
    Top10Struct* top10Struct = (Top10Struct*)data;
    g_hash_table_destroy(top10Struct->top10Table);
    g_free(top10Struct);
}

void free_top10_per_week(gpointer data) {
    Top10PerWeek* top10PerWeek = (Top10PerWeek*)data;
    g_tree_destroy(top10PerWeek->artistDurationTree);
    g_free(top10PerWeek);
}

Top10Struct* create_top10_struct() {
    Top10Struct* top10Struct = g_new(Top10Struct, 1);
    top10Struct->min_week_offset = -1;
    top10Struct->max_week_offset = -1;
    top10Struct->top10Table = g_hash_table_new_full(g_int_hash, g_int_equal, g_free, free_top10_per_week);

    return top10Struct;
}

GTree* get_artistDurationTree_by_week(Top10Struct *top10Struct, int week_offset) {
    Top10PerWeek *top10PerWeek = g_hash_table_lookup(top10Struct->top10Table, &week_offset);
    if (top10PerWeek == NULL) return NULL;
    return top10PerWeek->artistDurationTree;
}

int* get_top_10_by_week_from_top10(Top10Struct *top10Struct, int week_offset) {
    Top10PerWeek *top10PerWeek = g_hash_table_lookup(top10Struct->top10Table, &week_offset);
    if (top10PerWeek == NULL) return NULL;
    return top10PerWeek->top10;
}

void add_to_artistTree(GTree* artistDurationTree, int artist_id, int duration) {
    // Create the key and value
    int* key = g_new(int, 1);
    *key = artist_id;
    int *duration_ptr = g_tree_lookup(artistDurationTree, key);

    // Insert or update the tree
    if (duration_ptr == NULL) {
        int* value = g_new(int, 1);
        *value = duration;
        g_tree_insert(artistDurationTree, key, value);
    } else {
        *duration_ptr += duration;
        g_free(key); // Free the key as it is not needed
    }
}

void add_to_artistDurationTree_struct_from_top10(Top10Struct* top10Struct , int week_offset, int artist_id, int duration) {
    Top10PerWeek *top10PerWeek = g_hash_table_lookup(top10Struct->top10Table, &week_offset);

    if (top10PerWeek == NULL) {
        top10PerWeek = g_new(Top10PerWeek, 1);
        top10PerWeek->artistDurationTree = g_tree_new_full((GCompareDataFunc)cmp_int_pointer_with_data, NULL, g_free, g_free);
        for (int i = 0; i < 10; i++) {
            top10PerWeek->top10[i] = -1;
        }
        int *key = g_new(int, 1);
        *key = week_offset;
        g_hash_table_insert(top10Struct->top10Table, key, top10PerWeek);
    }

    add_to_artistTree(top10PerWeek->artistDurationTree, artist_id, duration);
}

GList* get_weeks_with_history(Top10Struct* top10Struct) {
    return g_hash_table_get_keys(top10Struct->top10Table);
}

void get_min_and_max_week_offset_from_top10(Top10Struct* top10Struct, int* min_week_offset, int* max_week_offset) {
    *min_week_offset = top10Struct->min_week_offset;
    *max_week_offset = top10Struct->max_week_offset;
}

void actualize_min_and_max_week_offset(Top10Struct* top10Struct, int week_offset) {
    if (top10Struct->min_week_offset == -1 || week_offset < top10Struct->min_week_offset) {
        top10Struct->min_week_offset = week_offset;
    }
    if (top10Struct->max_week_offset == -1 || week_offset > top10Struct->max_week_offset) {
        top10Struct->max_week_offset = week_offset;
    }
}















