#include "./data/catalogs/artists_catalog.h"
#include "./data/catalogs/catalogs_utils/artist_discography.h"
#include "./queries/query_artist_discography.h"
#include "./utils/type.h"
#include <stdio.h>
#include "./utils/time.h"
#include <ncurses.h>

typedef struct query_artist_discography {
    ArtistDiscography* element;
    struct query_artist_discography* next;
} Query_artist_discography;

Query_artist_discography* create_node(ArtistDiscography* data) {
    Query_artist_discography* new_node = malloc(sizeof(Query_artist_discography));
    if (!new_node) return NULL;

    new_node->element = data;
    new_node->next = NULL;
    return new_node;
}

Query_artist_discography* append_to_list(Query_artist_discography* head, ArtistDiscography* element) {
    // Allocate memory for a new node
    Query_artist_discography* new_node = malloc(sizeof(Query_artist_discography));
    if (!new_node) { // Check if memory allocation failed
        perror("Memory allocation failed");
        exit(EXIT_FAILURE); // Exit the program if malloc fails
    }

    // Initialize the new node
    new_node->element = element; // Store the given data in the node
    new_node->next = NULL;       // Set next to NULL since it's the last node

    // If the list is currently empty, return the new node as the head
    if (head == NULL) {
        return new_node;
    }

    // Otherwise, traverse to the end of the list
    Query_artist_discography* current = head;
    while (current->next != NULL) { // Move through the list until we reach the last node
        current = current->next;
    }

    // Append the new node to the end
    current->next = new_node;

    // Return the head of the list (unchanged)
    return head;
}


void free_query_artist_discography(void* to_free){
    Query_artist_discography* head = (Query_artist_discography*) to_free;
    Query_artist_discography* current = head;
    Query_artist_discography* temp;

    while (current != NULL) {
        temp = current;           // Save the current node
        current = current->next;  // Move to the next node

        // Ensure the pointer is valid before freeing
        if (temp) {
            free(temp);           // Free the current node
        }
    }

}


char** artist_discography_iterator(void* void_to_array_string, int num_to_print) {

    Query_artist_discography* to_string = (Query_artist_discography*)void_to_array_string; 
    
    char** string = malloc(num_to_print * sizeof(char*));
    if (!string) return NULL; 

    for (int i = 0; to_string != NULL && i < num_to_print; i += 4){

        ArtistDiscography* current = to_string->element;

        string[i] = get_artist_discography_name(current);
        string[i + 1] = strdup(convert_type(get_artist_discography_type(current)));
        string[i+2] = convert_seconds_to_time(get_artist_discography_discography(current)); 
        
        char* buff = get_artist_discography_country(current); 
        string[i+3] = malloc(strlen(buff) + 2); 
        snprintf(string[i+3], strlen(buff) + 2, "%s\n", buff);
        free(buff); 

        to_string = to_string->next;
    }
     
    return string;
}

void print_list(Query_artist_discography* head) {
    Query_artist_discography* current = head;
    while (current != NULL) {
        char* name = get_artist_discography_name(current->element);
        char* country = get_artist_discography_country(current->element);
        int type = get_artist_discography_type(current->element);
        int discography = get_artist_discography_discography(current->element);

        printf("Name: %s, Country: %s, Type: %d, Discography: %d\n", name, country, type, discography);

        free(name);
        free(country);
        current = current->next;
    }
}



int query_artist_discography(void** to_fill, DataBase* database, char* input) {
    char* n_artists = NULL;
    char* country = NULL;
    Query_artist_discography* output = NULL; // Initialize output

    // Parse number of artists
    char* token = strtok(input, " ");
    if (token != NULL) {
        n_artists = strdup(token); 
    }
    int num_of_artist = atoi(n_artists);

    // Parse country (if specified)
    token = strtok(NULL, "\"");
    if (token != NULL) {
        country = strdup(token);
    }

    // Handle query if n_artists != "0"
    int i = 0;
    if (strcmp(n_artists, "0")) {
        ArtistDiscography** answer = top_N_artists(get_artists_catalog(database), n_artists, country);

        for (i = 0; i < num_of_artist && answer[i] != NULL; i++) {
            output = append_to_list(output, answer[i]); // Update head
        }

        free(answer);
    }

    // Free dynamically allocated memory
    free(n_artists);
    free(country);

    // Assign output to to_fill
    *to_fill = output;

    return i * 4; // Example return value (modify as needed)
}

