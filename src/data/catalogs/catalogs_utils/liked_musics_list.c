#include "./data/catalogs/catalogs_utils/liked_musics_list.h"

typedef struct likedMusicsList {
    GSList* list;
} LikedMusicsList;

typedef struct likesByAge {
    int age;
    int likes;
} LikesByAge;

LikedMusicsList* initialize_liked_musics_list(){
    LikedMusicsList* liked_musics_list = g_malloc(sizeof(LikedMusicsList));
    liked_musics_list->list = NULL;

    return liked_musics_list;
}

void free_likes_by_age(LikesByAge* likes_by_age){
    free(likes_by_age);
}

void free_liked_musics_list(LikedMusicsList* list) {
    g_slist_free_full(list->list, (GDestroyNotify)free_likes_by_age);
    g_free(list);
}

LikesByAge* create_likes_by_age(int age, int likes){
    LikesByAge* likes_by_age = g_malloc(sizeof(LikesByAge));
    likes_by_age->age = age;
    likes_by_age->likes = likes;

    return likes_by_age;
}

LikedMusicsList* insert_to_liked_musics_list(LikedMusicsList* list, int age) {
    GSList* node = list->list;
    GSList* prev = NULL;

    // Traverse the list to accumulate likes and find the correct position or existing age
    while (node != NULL) {
        LikesByAge* data = (LikesByAge*)node->data;
        if (data->age >= age) {
            // Increment likes for all nodes with ages less than or equal to the given age
            data->likes += 1;
            
        } else {
            // Found the position to insert the new age
            break;
        }
        prev = node;
        node = node->next;
    }

    // If the age already exists, increment likes and return
    if (prev != NULL && ((LikesByAge*)prev->data)->age == age) {
        return list;
    }

    // Create a new node with the given age and likes 
    LikesByAge* new_likes_by_age;
    if (node != NULL) {
        // Use the next node's likes if previous likes were 0 
        LikesByAge* next_data = (LikesByAge*)node->data;
        new_likes_by_age = create_likes_by_age(age, next_data->likes + 1);
    } else {
        new_likes_by_age = create_likes_by_age(age, 1);
    }

    // Insert the new node in the sorted order
    list->list = g_slist_insert_sorted(list->list, new_likes_by_age, compare_liked_musics_list);
    
    return list;
}

gint compare_liked_musics_list(gconstpointer a, gconstpointer b) {
    const LikesByAge* age_a = (const LikesByAge*)a;
    const LikesByAge* age_b = (const LikesByAge*)b;
    return age_b->age - age_a->age; // Descending order
}

int get_likes_by_age_group(LikedMusicsList* list, int min_age, int max_age) {
    GSList* node = list->list;
    int min_age_likes = 0, max_age_likes = 0;

    while (node != NULL) {
        LikesByAge* data = node->data;

        if (data->age <= max_age && max_age_likes == 0) {
            max_age_likes = data->likes;
        }
        if (data->age < min_age) {
            min_age_likes = data->likes;
            break;
        }

        node = node->next;
    }
    return max_age_likes - min_age_likes;
}
