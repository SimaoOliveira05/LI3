#include "./data/catalogs/catalogs_utils/recommender.h"

typedef struct recommender {
    int **matrizClassificacaoMusicas;
    char **idsUtilizadores;
    char **nomesGeneros;
    int numUtilizadores;
    int numGeneros;
} Recommender;


Recommender* create_recommender(int userSize, int genreSize){
    Recommender* recommender = malloc(sizeof(Recommender));
    recommender->numUtilizadores = 0;
    recommender->numGeneros = 0;
    recommender->idsUtilizadores = malloc(userSize * sizeof(char*));
    recommender->nomesGeneros = malloc(genreSize * sizeof(char*));
    recommender->matrizClassificacaoMusicas = malloc(2 * userSize * sizeof(int*));

    // Allocate memory for each row (user)
    for (int i = 0; i < userSize; i++) {
        recommender->matrizClassificacaoMusicas[i] = malloc(2 * genreSize * sizeof(int));
        // Initialize the matrix with zeros
        for (int j = 0; j < genreSize; j++) {
            recommender->matrizClassificacaoMusicas[i][j] = 0;
        }
    }

    return recommender;
}



void free_recommender(Recommender* recommender){

    if (recommender == NULL) return;
    
    // Free each user's ID and their corresponding row in the matrix
    for(int i = 0; i < recommender->numUtilizadores; i++){
        free(recommender->idsUtilizadores[i]);
        free(recommender->matrizClassificacaoMusicas[i]);
    }

    // Free each genre name
    for(int i = 0; i < recommender->numGeneros; i++){
        free(recommender->nomesGeneros[i]);
    }

    // Free the arrays of pointers
    free(recommender->idsUtilizadores);
    free(recommender->nomesGeneros);
    free(recommender->matrizClassificacaoMusicas);

    // Free the recommender structure itself
    free(recommender);
}

int **get_recommender_matrix(Recommender* recommender){
    return recommender->matrizClassificacaoMusicas;
}

char **get_recommender_user_ids(Recommender* recommender){
    return recommender->idsUtilizadores;
}

char **get_recommender_genre_names(Recommender* recommender){
    return recommender->nomesGeneros;
}

int get_recommender_num_users(Recommender* recommender){
    return recommender->numUtilizadores;
}

int get_recommender_num_genres(Recommender* recommender){
    return recommender->numGeneros;
}

void increment_user_count(Recommender* recommender){
    recommender->numUtilizadores++;
}

void add_user_to_recommender(Recommender* recommender, char* id){
    recommender->idsUtilizadores[recommender->numUtilizadores] = strdup(id);
}


void add_like_to_recommender(Recommender* recommender, char* genre){
    // Check if the genre already exists
    for (int i = 0; i < recommender->numGeneros; i++) {
        if (strcmp(recommender->nomesGeneros[i], genre) == 0) {
            recommender->matrizClassificacaoMusicas[recommender->numUtilizadores][i] += 1;
            return;
        }
    }
    // If the genre does not exist, add it to the list
    recommender->nomesGeneros[recommender->numGeneros] = strdup(genre);
    recommender->matrizClassificacaoMusicas[recommender->numUtilizadores][recommender->numGeneros] += 1;
    recommender->numGeneros++;
}
