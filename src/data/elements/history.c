#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // Include the header for strcasecmp


typedef struct timestamp{
    char* date;
    char* time;
} TimeStamp;

typedef struct history {
    int user_id;
    int music_id;
    TimeStamp timestamp;
    int duration;
    short int platform; // 0-mobile  1-desktop
} History;

History* initialize_history() {
    History* history_instance = malloc(sizeof(struct history));

    history_instance->timestamp.date = NULL;
    history_instance->timestamp.time = NULL;


    return history_instance;
}

History* create_history(char* user_id, char* music_id, char* date, char* time, int duration, char* platform) {

    History* history_instance = initialize_history();
    
    history_instance->user_id = atoi(user_id+1);
    history_instance->music_id = atoi(music_id+1);
    history_instance->timestamp.date = strdup(date);
    history_instance->timestamp.time = strdup(time);
    history_instance->duration = duration;
    if (strcasecmp(platform,"mobile") == 0)
        history_instance->platform = 0;
    if (strcasecmp(platform,"desktop") == 0)
        history_instance->platform = 1;

    return history_instance;
}


void free_history(History* history) {
    free(history->timestamp.date);
    free(history->timestamp.time);
    free(history);
}

int get_history_user_id(History* history) {
    return history->user_id;
}

void set_history_user_id(History* history, int user_id) {
    history->user_id = user_id;
}

int get_history_music_id(History* history) {
    return history->music_id;
}

void set_history_music_id(History* history, int music_id) {
    history->music_id = music_id;
}

char* get_history_time(History* history) {
    return strdup(history->timestamp.time);
}

void set_history_time(History* history, char* time) {
    history->timestamp.time = strdup(time);
}

char* get_history_date(History* history) {
    return strdup(history->timestamp.date);
}

void set_history_date(History* history, char* date) {
    history->timestamp.date = strdup(date);
}

int get_history_duration(History* history) {
    return history->duration;
}

void set_history_duration(History* history, int duration) {
    history->duration = duration;
}

int get_history_platform(History* history) {
    return history->platform;
}

void set_history_platform(History* history, short int platform) {
    history->platform = platform;
}

