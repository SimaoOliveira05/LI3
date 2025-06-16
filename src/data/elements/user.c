#include "./data/elements/user.h"
#include "./data/elements/history.h"
#include "./data/catalogs/catalogs_utils/our_recommender.h"

typedef enum subscriptionType {
    normal,
    premium
} SubscriptionType;

typedef struct user {
    int username;
    char* email;
    char* first_name;
    char* last_name;
    char* birth_date;
    char* country;
    SubscriptionType subscription_type;
    GArray* liked_music_id;
    UserRecommender* recommender;
} User;


UserRecommender* get_user_recommender(User* user){
    return user->recommender;
}

User* create_user(char* username, char* email, char* first_name, char* last_name, char* birth_date, char* country, char* subscription_type, GArray* liked_music_id) {
    
    User* user_instance = initialize_user();
    
    user_instance->username = atoi(username+1) ;
    user_instance->email = strdup(email);
    user_instance->first_name = strdup(first_name);
    user_instance->last_name = strdup(last_name);
    user_instance->birth_date = strdup(birth_date);
    user_instance->country = strdup(country);
    user_instance->subscription_type = atoi(subscription_type);
    user_instance->liked_music_id = liked_music_id;
    return user_instance;
}

User* initialize_user() {
    User* user_instance = malloc(sizeof(struct user));

    user_instance->email = NULL;
    user_instance->first_name = NULL;
    user_instance->last_name = NULL;
    user_instance->birth_date = NULL;
    user_instance->country = NULL;
    user_instance->liked_music_id = NULL;
    user_instance->recommender = initialize_user_recommender();
    return user_instance;
}

void free_user(User* user) {
    free(user->email);
    free(user->first_name);
    free(user->last_name);
    free(user->birth_date);
    free(user->country);
    g_array_free(user->liked_music_id, TRUE);
    free_user_recommender(user->recommender);
    free(user);
}

int get_user_username(User* user) {
    return user->username;
}

void set_user_username(User* user, int username) {
    user->username = username;
}

char* get_user_email(User* user) {
    return strdup(user->email);
}

void set_user_email(User* user, char* email) {
    user->email = strdup(email);
}

char* get_user_first_name(User* user) {
    return strdup(user->first_name);
}

void set_user_first_name(User* user, char* first_name) {
    user->first_name = strdup(first_name);
}

char* get_user_last_name(User* user) {
    return strdup(user->last_name);
}

void set_user_last_name(User* user, char* last_name) {
    user->last_name = strdup(last_name);
}

char* get_user_birth_date(User* user) {
    return strdup(user->birth_date);
}

void set_user_birth_date(User* user, char* birth_date) {
    user->birth_date = strdup(birth_date);
}

char* get_user_country(User* user) {
    return strdup(user->country);
}

void set_user_country(User* user, char* country) {
    user->country = strdup(country);
}

SubscriptionType get_user_subscription_type(User* user) {
    return user->subscription_type;
}

void set_user_subscription_type(User* user, SubscriptionType subscription_type) {
    user->subscription_type = subscription_type;
}

GArray* get_user_liked_music_id(User* user) {
    return g_array_copy(user->liked_music_id);
}


int get_user_liked_music_size(User* user) {
    return user->liked_music_id->len;
}

void set_user_liked_music_id(User* user, GArray* liked_music_ids) {
    user->liked_music_id = liked_music_ids;
}

