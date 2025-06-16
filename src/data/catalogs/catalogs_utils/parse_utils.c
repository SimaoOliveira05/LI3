#include "./data/catalogs/catalogs_utils/parse_utils.h"


GArray* format_ids_list(const char* artist_ids_str) {
    
    //Flag that dictates if we are in the first index of the list, important to know if we are in the first index, if not , we need to remove the " " in each index
    int flag = 0;

    GArray* ids_list = g_array_new(FALSE,FALSE,sizeof(int));

    // Check if the input string is "[]"
    if (strcmp(artist_ids_str, "[]") == 0) {
        return ids_list;
    }

    // Copy the input string to a modifiable buffer
    char* buffer = strdup(artist_ids_str);

    // Remove the '[' and ']' characters
    buffer[strlen(buffer) - 1] = '\0'; // Remove the trailing ']'
    char* ids = buffer + 1; // Skip the leading '['

    char* token;
    
    
    while ((token = strsep(&ids, ",")) != NULL) {

        // Remove leading and trailing single quotes
        if (flag == 1) token++;
        if (token[0] == '\'') token++;
        if (token[strlen(token) - 1] == '\'') token[strlen(token) - 1] = '\0';

        // Add to the array of strings inside the appropriate struct
        int value = atoi(token + 1);
        g_array_append_val(ids_list, value);

        flag = 1;
    }
        
    free(buffer);

    return ids_list;

}



