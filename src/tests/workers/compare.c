#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ERROR 100

typedef struct
{
    int file_number;
    int line_number[MAX_ERROR];
    int differences;
} Error;

Error compare_files(const char *result_folder, const char *expected_folder, int command_counter){

    char result_path[256];
    char expected_path[256];

    sprintf(result_path, "%s/command%d_output.txt", result_folder, command_counter);
    sprintf(expected_path, "%s/command%d_output.txt", expected_folder, command_counter);

    FILE *file1 = fopen(result_path, "r");
    FILE *file2 = fopen(expected_path, "r");

    Error error;
    error.file_number = command_counter;
    error.differences = 0;
    memset(error.line_number, 0, sizeof(error.line_number));

    if (file1 == NULL){
        printf("Error opening result file.\n");

        return error;
    }

    if (file2 == NULL){
        printf("Error opening expected files.\n");

        return error;
    }

    char line1[1000], line2[1000];
    int line_number = 0;

    while (fgets(line1, sizeof(line1), file1) != NULL && fgets(line2, sizeof(line2), file2) != NULL) {
        line_number++;
        
        if (strcmp(line1, line2) != 0) {
            if (error.differences < MAX_ERROR) {
                error.line_number[error.differences] = line_number;
                error.differences++;
            } else {
                break;
            }
        }
    }

    // Check if one file has extra lines
    if (error.differences == 0) {
        if (fgets(line1, sizeof(line1), file1) != NULL || fgets(line2, sizeof(line2), file2) != NULL) {
            line_number++;
            if (error.differences < MAX_ERROR) {
                error.line_number[error.differences] = line_number;
                error.differences++;
            }
        }
    }
    fclose(file1);
    fclose(file2);

    return error;
}
