#include "./file_workers/writer.h"

#include <stdio.h>
#include <stdlib.h>

void write_in_file(char* file_path, char* line_to_write){ //CONFIRMAR SE PASSAR FILE COMO ARGUMENTO É CORRETO


    //LEMBRAR DE TIRAR ISTO QUANDO Q4 ESTIVER FEITA
    if (!line_to_write) {
        return;
    }

    FILE* fp = fopen(file_path, "a");
    
    
    if (fp) {
        fputs(line_to_write, fp);
        fclose(fp);
    } else {
        perror("Error opening file");
    }

}

void write_query_response(int query_num, char* response) {

    int digits = 0, copy_qn = query_num;
    while (copy_qn != 0) {
        copy_qn /= 10;
        digits++;
    }

    char* result_path = malloc(31 + digits + 1);
    sprintf(result_path, "./resultados/command%d_output.txt", query_num);

    //printf("Writing to file: %s\n", result_path);
    
    write_in_file(result_path, response);

    free(result_path);

}

void write_error(StructType type, char* line_to_add){

    //printf("ERROR IN LINE : %s\n", line_to_add);

    char* path_to_errors = "./resultados";
    int path_len = strlen(path_to_errors);

    char* path_to_error_file = NULL;

    switch (type){
    case ARTIST:

        path_to_error_file = malloc(path_len+20);
        sprintf(path_to_error_file, "%s/artists_errors.csv", path_to_errors);
        
        break;

    case USER:

        path_to_error_file = malloc(path_len+20);
        sprintf(path_to_error_file, "%s/users_errors.csv", path_to_errors);
        
        break;

    case MUSIC:

        path_to_error_file = malloc(path_len+20);
        sprintf(path_to_error_file, "%s/musics_errors.csv", path_to_errors);
        
        break;

    case HISTORY:

        path_to_error_file = malloc(path_len+20);
        sprintf(path_to_error_file, "%s/history_errors.csv", path_to_errors);
        
        break;

    case ALBUM:

        path_to_error_file = malloc(path_len+20);
        sprintf(path_to_error_file, "%s/albums_errors.csv", path_to_errors);
        
        break;
    
    default:
        break;
    }
    
    write_in_file(path_to_error_file, line_to_add);

    free(path_to_error_file);

}