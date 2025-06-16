#include "./workers/queries_worker.h"
#include "./file_workers/writer.h"
#include "./queries/query_person_summary.h"
#include "./queries/query_artist_discography.h"
#include "./queries/query_genres_by_age_group.h"
#include "./queries/query_artist_on_top_10_more_often.h"
#include "./queries/query_user_year_summary.h"
#include "./queries/query_user_recommender.h"
#include "./interactive/interactive_querying.h"

#include <stdio.h>
#include <string.h>

char get_separator(char second_char){
    
    if (second_char == ' ' || second_char == '\n'){
        return ';';
    }else{
        return '=';
    }
    
}

void prepare_answer_to_write(int command_counter, void* unformatted_answer, int num_of_params, char** (*answer_iterator)(void*, int), void (*free_answer)(void*), char separator, int mode, WINDOW* window, char* line){
    if (unformatted_answer != NULL && num_of_params != 0){    
        
        char** list_of_answer_parameters = answer_iterator(unformatted_answer, num_of_params);

        int num_strings = num_of_params;
        
        int total_length = 0;
        for (int i = 0; i < num_strings; i++){
            total_length += strlen(list_of_answer_parameters[i]);       
            if (i < num_strings - 1)             
                total_length += 1;
        }

        char* query_answer = malloc(total_length + 1);
        int new_line = 1;

        query_answer[0] = '\0';
        for (int i = 0; i < num_strings; i++) {
            if (list_of_answer_parameters[i][strlen(list_of_answer_parameters[i]) - 1] == '\n') 
                new_line = 0;
            
            strcat(query_answer, list_of_answer_parameters[i]); 
            
            if (i < num_strings - 1 && new_line == 1) 
                strncat(query_answer, &separator, 1);
                
            new_line = 1;
        }
        if(mode == 1 || mode == 2){
            draw_interactive_response(window, line, query_answer);
        }
        if(mode == 0 || mode == 2){
            write_query_response(command_counter, query_answer);
        }
        for (int i = 0; i < num_strings; i++) {
            free(list_of_answer_parameters[i]);
        } 

        free(list_of_answer_parameters); 
        free(query_answer);

    }else{
        write_query_response(command_counter, "\n");
    }

    if(free_answer != NULL && unformatted_answer != NULL) 
        free_answer(unformatted_answer);
    
}

int format_and_write_query_answer(int command_counter,char* line,DataBase* database, int mode, WINDOW* window){ 
        
    char *line_copy = strdup(line);
    char *token;
    char *saveptr;

    char separator = get_separator(line_copy[1]);

    token = strtok_r(line_copy, " ", &saveptr);
    char num = token[0]; 

    char *query_input = strtok_r(NULL, "\n", &saveptr); 
    
    void* query_answer = NULL;
    char** (*answer_iterator)(void*, int) = NULL;
    void (*free_answer)(void*) = NULL;
    int num_of_answer_params = 0;
    
    switch (num){
        case '1':
            num_of_answer_params = query_person_summary(&query_answer, database, query_input);
            answer_iterator = person_summary_iterator;
            free_answer = free_person_summary;
            break;

        case '2':
            num_of_answer_params = query_artist_discography(&query_answer, database, query_input);
            answer_iterator = artist_discography_iterator;
            free_answer = free_query_artist_discography;

            break;

        case '3':
            num_of_answer_params = query_genre_by_age_group(&query_answer, database, query_input);
            answer_iterator = genre_by_age_group_iterator;   
            free_answer = free_query_genres_by_age_group;       
            break;

        case '4':
            num_of_answer_params = query_artist_on_top_10(&query_answer, database, query_input);
            answer_iterator = artist_on_top_10_more_often_iterator;   
            free_answer = free_artist_on_top_10_more_often;
            break;

        case '5':
        

            num_of_answer_params = query_user_recommender_original(&query_answer, database, query_input);
            //num_of_answer_params = query_user_recommender_self(&query_answer, database, query_input);
            answer_iterator = user_recommender_iterator;
            free_answer = free_query_user_recommender;
            break;

        case '6':
            num_of_answer_params = query_user_year_summary(&query_answer, database, query_input);
            answer_iterator = user_year_summary_iterator; 
            free_answer = free_query_user_year_summary;  
            break;
        
        default:
        
            break;
        }

        prepare_answer_to_write(command_counter, query_answer, num_of_answer_params, answer_iterator, free_answer, separator, mode, window, line);

        free(line_copy); 
        
        int queryNum = num - '0';
        return queryNum;
}



int queries_worker(DataBase* database, char* input_path, int mode, WINDOW* window) {
    char* line = NULL;
    size_t length = 0;
    static int command_counter = 0;
    if(mode == 0){
        printf("\n=========================================\n");
        printf("        STARTING QUERY PROCESSING        \n");
        printf("=========================================\n\n");

        int command_counter = 0;
        FILE* fp = fopen(input_path, "r");

        if (!fp) {
            perror("❗ Error opening input file");
            return 2;
        }
        
        while (getline(&line, &length, fp) != -1) {
            command_counter++;
            printf("🔄 Processing Query %d...\n", command_counter);
            printf("🔍 Query: %s\n", line);
            format_and_write_query_answer(command_counter, line, database, mode, NULL);
        }

        fclose(fp);
        free(line);

        printf("\n\n✅ Total Queries Processed: %d\n", command_counter);

        printf("\n=========================================\n");
        printf("        QUERY PROCESSING COMPLETED       \n");
        printf("=========================================\n");

        return 0;
    }else {
        
        line = handle_query_execution(window);
        if (line == NULL) {
            return 1;
        } else {
            command_counter++;
            format_and_write_query_answer(command_counter, line, database, mode, window);
            return 0;
        }
    }
}

