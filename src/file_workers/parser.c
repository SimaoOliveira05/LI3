#include "./file_workers/parser.h"
#include "./file_workers/writer.h"
#include "./data/database_validations.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void remove_quotes(char* str){
    if (str == NULL || strlen(str) < 2) {
        return;
    }

    size_t len = strlen(str);
    if (str[0] == '"' && str[len - 1] == '"') {
        // Shift the string one position to the left
        memmove(str, str + 1, len - 1);
        // Replace the last quote with a null terminator
        str[len - 2] = '\0';
    }
}


int parser(void* database, char* path, ProcessLineFunc process_line) {
    FILE* fp = fopen(path, "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    char *line = NULL;
    size_t length = 0;
    int num_of_tokens = 0;
    int counter = -1;
    int invalids = 0;

    // Read the header line to determine the number of tokens
    if (getline(&line, &length, fp) != -1) {
        char *line_copy = strdup(line);
        char *token;
        char *saveptr;

        // Count the number of tokens in the header
        token = strtok_r(line_copy, ";", &saveptr);
        while (token != NULL) {
            num_of_tokens++;
            token = strtok_r(NULL, ";", &saveptr);
        }

        printf("🔍 Number of Tokens Detected: %d\n", num_of_tokens);
        free(line_copy);
    }

    // Reposition the file pointer to the beginning of the file
    fseek(fp, 0, SEEK_SET);

    // Process each line in the file
    while (getline(&line, &length, fp) != -1) {
        counter++;
        char *line_copy = strdup(line);
        char *token;
        char *saveptr;
        int current_token_index = 0;

        // Allocate memory for the list of tokens
        char **list_of_tokens = malloc(num_of_tokens * sizeof(char*));

        // Tokenize the line
        token = strtok_r(line_copy, ";\n", &saveptr);
        while (token != NULL && current_token_index < num_of_tokens) {
            list_of_tokens[current_token_index] = strdup(token);
            remove_quotes(list_of_tokens[current_token_index]);
            current_token_index++;
            token = strtok_r(NULL, ";\n", &saveptr);
        }

        // Call the processing function
        int result = process_line(list_of_tokens, database, line);
        
        if (result == 1) {
            invalids++;
        }
        
        // If the processing function returns -1 there are no validations
        if (result == -1) {
            invalids = -1;
        }

        // Free allocated memory
        for (int i = 0; i < num_of_tokens; i++) {
            free(list_of_tokens[i]);
        }
        free(list_of_tokens);
        free(line_copy);
    }

    fclose(fp);
    free(line);

    //Only prints if user wants to see the number of invalid lines
    if (invalids != -1)
        printf("Processed %d lines with %d invalid lines.\n", counter, invalids);
    return counter-invalids;
}