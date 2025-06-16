#include <glib.h>
#include "./data/catalogs/catalogs_utils/history_data.h"
#include "./utils/cmp.h"
#include "./utils/time.h"
#include "./utils/format.h"

typedef struct ArtistData{
    int listeningTime; //Tempo total que o utilizador passou a ouvir o artista
    int musicCount; //Número de musicas diferents ouvidas pelo utilizador
} ArtistData;


typedef struct ArtistInfo {
    int artist_id;
    int listeningTime;
    int musicCount;
} ArtistInfo;


typedef struct HistoryData {
    GTree* albumTree; //Árvore binária balanceada que contem quanto tempo ouvio cada album
    GTree* genreTree; //Árvore binária balanceada que contem quanto tempo ouvio cada genero
    GTree* artistTree;
    GTree* musicTree;
    int mostHeardAlbum; //Album mais ouvido pelo utilizador
    int mostHeardAlbumTime; //Tempo total que o utilizador passou a ouvir o album mais ouvido
    int hourList[24]; //Array que contem o número de musicas ouvidas em cada hora do dia
    int dayList[365]; //Array que contem o número de musicas ouvidas em cada dia do ano
    int musicCount; //Musicas ouvidas no total pelo utilizador
    int totalListeningTime;
    
    ArtistInfo** mostHeardArtists; //Top n artistas (n passado pela query)
} HistoryData;

ArtistInfo* initialize_artistInfo(){
    ArtistInfo* artistInfo_instance = malloc(sizeof(struct ArtistInfo));
    if (artistInfo_instance != NULL) {
        artistInfo_instance->artist_id = 0;
        artistInfo_instance->listeningTime = 0;
        artistInfo_instance->musicCount = 0;
    }
    return artistInfo_instance;
}

HistoryData* initialize_historyData(int nArtists){
    HistoryData* historyData_instance = malloc(sizeof(struct HistoryData));
    historyData_instance->albumTree = g_tree_new_full(cmp_int_pointer_with_data, NULL, g_free, g_free);
    historyData_instance->genreTree = g_tree_new_full(strcmp_wrapper, NULL, g_free, g_free);
    historyData_instance->artistTree = g_tree_new_full(cmp_int_pointer_with_data, NULL, g_free, g_free);
    historyData_instance->musicTree = g_tree_new_full(cmp_int_pointer_with_data, NULL, g_free, NULL);
    historyData_instance->mostHeardAlbum = 0;
    historyData_instance->mostHeardAlbumTime = 0;
    historyData_instance->totalListeningTime = 0;
    for(int i = 0; i < 24; i++){
        historyData_instance->hourList[i] = 0;
    }
    for(int i = 0; i < 365; i++){
        historyData_instance->dayList[i] = 0;
    }
    historyData_instance->musicCount = 0;
    historyData_instance->mostHeardArtists = malloc(nArtists * sizeof(ArtistInfo*));

if (historyData_instance->mostHeardArtists != NULL) {
    for(int i = 0; i < nArtists; i++){
        historyData_instance->mostHeardArtists[i] = initialize_artistInfo();
    }
}
    return historyData_instance;
}

void free_historyData(HistoryData* historyData,int nArtists){
    g_tree_destroy(historyData->albumTree);
    g_tree_destroy(historyData->genreTree);
    g_tree_destroy(historyData->artistTree);
    g_tree_destroy(historyData->musicTree);
    for(int i = 0; i < nArtists; i++){
        free(historyData->mostHeardArtists[i]);
    }
    free(historyData->mostHeardArtists);
    free(historyData);
}


ArtistData* initialize_artistData(){
    ArtistData* artistData_instance = malloc(sizeof(struct ArtistData));
    artistData_instance->listeningTime = 0;
    artistData_instance->musicCount = 0;
    return artistData_instance;
}


int compare_artist_info(const void *a, const void *b) {
    const ArtistInfo *artistA = *(const ArtistInfo **)a;
    const ArtistInfo *artistB = *(const ArtistInfo **)b;
    if (artistA->listeningTime < artistB->listeningTime)
        return 1;
    else if (artistA->listeningTime > artistB->listeningTime)
        return -1;
    else if(artistA->artist_id > artistB->artist_id)
        return 1;
    else
        return -1;
}

void sort_artist_info(ArtistInfo **artists, size_t nArtists) {

    qsort(artists, nArtists, sizeof(ArtistInfo *), compare_artist_info);
}


void add_to_album_tree(HistoryData* historyData,int album_id,int duration){
    //Preencher a árvore de albums
    int *albumkey = g_new(int,1);
    *albumkey = album_id;
    int* albumCount = g_tree_lookup(historyData->albumTree,albumkey);
    //Caso não existir esse album na árvore, cria-se um novo albumData e insere-se na árvore
    if(albumCount == NULL){
        albumCount = malloc(sizeof(int));
        *albumCount = 0;
        g_tree_insert(historyData->albumTree,albumkey,albumCount);
    }
    else
        g_free(albumkey);

    *albumCount += duration;
        
    //Verificar se o album é o mais ouvido
    if (*albumCount > historyData->mostHeardAlbumTime){
        historyData->mostHeardAlbum = album_id;
        historyData->mostHeardAlbumTime = *albumCount;
    }
}

void add_to_genre_tree(HistoryData* historyData, char* genre,int duration){
    //Preencher a árvore de generos
    int *genreCount = g_tree_lookup(historyData->genreTree,genre);
        
    if(genreCount == NULL){
        genreCount = malloc(sizeof(int));
        *genreCount = duration;
        g_tree_insert(historyData->genreTree,genre,genreCount);
    }
    else{
        *genreCount += duration;
    }
}


void add_to_artist_tree(HistoryData* historyData, GArray* artistList,int music_id, int nArtists,int duration){
    for(guint i = 0; i < artistList->len; i++){
        int artist_id = g_array_index(artistList,int,i); //id do artista
        int *artist_key = g_new(int,1); //Inicializar a key do artista
        *artist_key = artist_id;
        ArtistData* artistData = g_tree_lookup(historyData->artistTree,artist_key); //Ver se o artista já existe na árvore
        
        if(artistData == NULL){//Não existe
            artistData = initialize_artistData();
            artistData->listeningTime += duration;
            artistData->musicCount += 1;

            g_tree_insert(historyData->artistTree,artist_key,artistData);
                
            //Incrementar o número de musicas ouvidas pelo utilizador e insere-se a musica na árvore de musicas
            int *music_key = g_new(int,1);
            *music_key = music_id;
            gboolean key_exists = g_tree_lookup_extended(historyData->musicTree, music_key, NULL,NULL);                    
            if(!key_exists){
                g_tree_insert(historyData->musicTree,music_key,NULL);
                historyData->musicCount++;
            }
            else
                g_free(music_key);
        }
        else{//Existe
            artistData->listeningTime += duration;
            artistData->musicCount++;
            int *music_key = g_new(int,1);
            *music_key = music_id;
            gboolean key_exists = g_tree_lookup_extended(historyData->musicTree, music_key, NULL, NULL);                    
            if(!key_exists){//A música ainda não tinha sido ouvida, logo incrementa-se o número de musicas ouvidas pelo utilizador e insere-se a musica na árvore de musicas
                g_tree_insert(historyData->musicTree,music_key,NULL);
                historyData->musicCount++;
            }
            else
                g_free(music_key);
            
            g_free(artist_key); // Como a key já existe na árvore, liberta-se 
        }
        //Verificar se o artista está no array de top nArtistas mais ouvidos
            if (artistData->listeningTime > historyData->mostHeardArtists[nArtists-1]->listeningTime){
                historyData->mostHeardArtists[nArtists-1]->listeningTime = artistData->listeningTime;
                historyData->mostHeardArtists[nArtists-1]->artist_id = artist_id;
                historyData->mostHeardArtists[nArtists-1]->musicCount = artistData->musicCount;
                sort_artist_info(historyData->mostHeardArtists, nArtists);
            }
    }
    g_array_free(artistList,TRUE); //Libertamos a lista de artistas copiada
}


void add_to_time(HistoryData* historyData, char* time, int duration){
    int hour, minutes, seconds;
    strsep_by_token(&hour, &minutes, &seconds, ":", time);
    historyData->hourList[hour] += duration;
    free(time);
}

void add_to_date(HistoryData* historyData, char* date){
    int day, month, year;
    strsep_by_token(&year, &month, &day, "/", date);
    int dayOfYear = day_of_year(month,day);
    historyData->dayList[dayOfYear] += 1;
    free(date);
}

char* get_listening_time(HistoryData* data){
    return convert_seconds_to_time(data->totalListeningTime);
}

int get_music_count(HistoryData* data){
    return data->musicCount;
}

char* get_most_listened_genre(HistoryData* data){
    
    GTree* genreTree = data->genreTree;
    GTreeNode *node = g_tree_node_first(genreTree);
    char* most_listened_genre = (char *)g_tree_node_key(node);
    int max_count = *(int *)g_tree_node_value(node);

    node = g_tree_node_next(node);
    
    while (node != NULL) {
        char* current_genre = (char *)g_tree_node_key(node);
        int *current_count = (int *)g_tree_node_value(node);
        if (*current_count > max_count) {
            max_count = *current_count;
            most_listened_genre = current_genre;
        }

        if (*current_count == max_count && strcmp(current_genre, most_listened_genre) < 0) {
            most_listened_genre = current_genre;
        }
        
        node = g_tree_node_next(node);
    }
    return strdup(most_listened_genre);
}

char* get_artist_id_by_index(HistoryData* data, int index){
    return format_artist_id(data->mostHeardArtists[index]->artist_id);
}

char* get_artist_time_by_index(HistoryData* data, int index){
    return convert_seconds_to_time(data->mostHeardArtists[index]->listeningTime);
}

int get_artist_time_by_index_int(HistoryData* data, int index){
    return data->mostHeardArtists[index]->listeningTime;
}

int get_artist_music_count_by_index(HistoryData* data, int index){
    return data->mostHeardArtists[index]->musicCount;
}

char* get_most_heard_album(HistoryData* data){
    return format_album_id(data->mostHeardAlbum);
}

int get_most_listened_hour(HistoryData* data){
    int most_listened_hour = 0;
    for(int i = 1; i < 24; i++){
        if(data->hourList[i] >= data->hourList[most_listened_hour])
            most_listened_hour = i;
    }
    return most_listened_hour;
}

void get_most_listened_date(HistoryData* data, int* month, int* day){
    int most_listened_day = 0;
    for(int i = 1; i < 365; i++){
        if (data->dayList[i] != 0)
        if(data->dayList[i] >= data->dayList[most_listened_day])
            most_listened_day = i;
    }
    month_day(most_listened_day, month, day);
}

HistoryData* build_history_data(GPtrArray* historyList, DataBase* database, int nArtists,char* year){
    
    if (historyList == NULL) {
        return NULL;
    }

    HistoryData* historyData = initialize_historyData(nArtists);
    
    int flag = 0; //Dita se foi encontrado alguma history associada ao ano (retornamos NULL se não houver)
    for(guint i = 0; i < historyList->len;i++){
        
        History* history = g_ptr_array_index(historyList,i);
        char* historyYear = malloc(5*sizeof(char)); 
        char* historyDate = get_history_date(history);
        get_year(historyDate,historyYear);
        free(historyDate);
        
        if (strcmp(year,historyYear) != 0){
            free(historyYear);
            continue;
        }
        flag = 1;

        free(historyYear);
        
        Music* music = get_music_by_id(get_musics_catalog(database),get_history_music_id(history));
            
        int album_id = get_music_album_id(music); 
        int music_id = get_music_id(music);
        int duration = get_history_duration(history);
        char* genre = get_music_genre(music);
        GArray* artistList = get_music_artist_id(music);

        add_to_album_tree(historyData,album_id,duration);

        add_to_genre_tree(historyData,genre,duration);

        add_to_artist_tree(historyData,artistList,music_id,nArtists,duration);

        add_to_time(historyData,get_history_time(history),duration);

        add_to_date(historyData,get_history_date(history));

        historyData->totalListeningTime += duration;
    }
    if (flag == 0){
        free_historyData(historyData,nArtists);
        return NULL;
    }
    
    return historyData; 
}                               

