#include "./interactive/interactive.h"
#include "./interactive/interactive_utilities.h"
#include "./workers/queries_worker.h"


#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>

typedef enum {
    DATASET_SELECTION,
    QUERY_EXECUTION,
    EXIT
} MenuState;

typedef struct programstate{
    char dataset_path[MAX_PATH];
    bool database_populated;
} ProgramState;

int is_valid_directory(const char* path) {
    struct stat sb;
    return (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode));
}

int is_valid_dataset(const char* path) {
    if (!is_valid_directory(path)) {
        return 0;
    }

    printf("Checking");
    
    const char* required_files[] = {
        "albums.csv", "artists.csv", "history.csv", 
        "musics.csv", "users.csv"
    };
    
    char filepath[512];
    for (int i = 0; i < 5; i++) {
        snprintf(filepath, sizeof(filepath), "%s/%s", path, required_files[i]);
        printf("Checking: %s\n", filepath);
        if (access(filepath, F_OK) == -1) {
            return 0;
        }
    }
    return 1;
}


void remove_quotes_Nprint(char* str){
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

bool handle_default_dataset_selection(WINDOW* win, DataBase* database, ProgramState* state) {
    wclear(win);
    box(win, 0, 0);
    
    char* choices[] = {
        "Small Dataset",
        "Big Dataset",
        "Go back"
    };
    int n_choices = 3;
    int highlight = 1;
    int choice = 0;
    
    while (choice == 0) {
        print_centered_message(win, 2, "Select Default Dataset Size:");
        
        for (int i = 0; i < n_choices; i++) {
            if (highlight == i + 1) {
                wattron(win, A_REVERSE);
            }
            print_centered_message(win, i + 4, choices[i]);
            wattroff(win, A_REVERSE);
        }
        
        int c = wgetch(win);
        switch (c) {
            case KEY_UP:
                highlight = (highlight == 1) ? n_choices : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight == n_choices) ? 1 : highlight + 1;
                break;
            case 10:  // Enter key
                choice = highlight;
                break;
        }
    }
    
    if (choice == 3) {  // Go back
        return false;
    }
    
    // Set the appropriate path based on selection
    const char* selected_path;
    if (choice == 1) {
        selected_path = "./fase2-small/small/dataset/com_erros";
        print_centered_message(win, 6, "Selected: Small Dataset");
    } else {
        selected_path = "../../fase2-big/fase2-dataset-big-com-erros/com_erros/";
        print_centered_message(win, 6, "Selected: Big Dataset");
    }
    
    wclear(win);
    box(win, 0, 0);
    print_centered_message(win, 2, "Populating database...");
    wrefresh(win);
    
    // Use populate_database_Nprint 
    endwin();
    initscr();
    char* path = strdup(selected_path);
    int result = populate_database(database, path, 0);
    free(path);
    refresh();
    
    // Show success/failure message and wait briefly
    wclear(win);
    box(win, 0, 0);
    if (result != 0) {  // Assuming 0 means success - adjust based on your implementation
        print_centered_message(win, 2, "Database populated successfully!");
        state->database_populated = true;
    } else {
        print_centered_message(win, 2, "Error populating database!");
        state->database_populated = false;
    }
    print_centered_message(win, 4, "Press any key to continue...");
    wrefresh(win);
    wgetch(win);
    
    return state->database_populated;
}

bool handle_dataset_selection(WINDOW* win, DataBase* database, ProgramState* state) {
    wclear(win);
    box(win, 0, 0);
    
    char* choices[] = {
        "Use default dataset",
        "Use custom dataset",
        "Go back"
    };
    int n_choices = 3;
    int highlight = 1;
    int choice = 0;
    
    while (choice == 0) {
        print_centered_message(win, 2, "Dataset Selection:");
        
        for (int i = 0; i < n_choices; i++) {
            if (highlight == i + 1) {
                wattron(win, A_REVERSE);
            }
            print_centered_message(win, i + 4, choices[i]);
            wattroff(win, A_REVERSE);
        }
        
        int c = wgetch(win);
        switch (c){
            case KEY_UP:
                highlight = (highlight == 1) ? n_choices : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight == n_choices) ? 1 : highlight + 1;
                break;
            case 10:  // Enter key
                choice = highlight;
                break;
        }
    }
    
    if (choice == 3) {  // Go back
        return false;
    }
    
    bool success;
    if (choice == 1) {  // Default dataset
        success = handle_default_dataset_selection(win, database, state);
    } else { 
        // Custom dataset
        wclear(win);
        box(win, 0, 0);
        print_centered_message(win, 2, "Enter the path to the dataset:");
        wrefresh(win);
        
        char dataset_path[MAX_PATH];
        move(4, 1);  // Move cursor to the line below the question
        echo();
        wgetnstr(win, dataset_path, MAX_PATH - 1);
        noecho();
        
        if (is_valid_dataset(dataset_path)) {
            wclear(win);
            box(win, 0, 0);
            print_centered_message(win, 2, "Populating database...");
            wrefresh(win);
            
            endwin();
            initscr();
            int result = populate_database(database, dataset_path, 0);
            refresh();
            
            wclear(win);
            box(win, 0, 0);
            if (result != 0) {
                print_centered_message(win, 2, "Database populated successfully!");
                state->database_populated = true;
            } else {
                print_centered_message(win, 2, "Error populating database!");
                state->database_populated = false;
            }
            print_centered_message(win, 4, "Press any key to continue...");
            wrefresh(win);
            wgetch(win);
            
            success = state->database_populated;
        } else {
            wclear(win);
            box(win, 0, 0);
            print_centered_message(win, 2, "Invalid dataset path!");
            print_centered_message(win, 4, "Press any key to continue...");
            wrefresh(win);
            wgetch(win);
            success = false;
        }
    }
    
    if (success) {
        // Clear screen and show transition message
        wclear(win);
        box(win, 0, 0);
        print_centered_message(win, 2, "Database populated successfully!");
        print_centered_message(win, 4, "Moving to query execution menu...");
        wrefresh(win);
        napms(1500);  // Show message for 1.5 seconds
    }
    
    return success;
}

int ask_to_write_to_file(WINDOW* win) {
    wclear(win);
    box(win, 0, 0);
    
    char* choices[] = {
        "Yes",
        "No"
    };
    int n_choices = 2;
    int highlight = 1;
    int choice = 0;
    
    while (choice == 0) {
        print_centered_message(win, 2, "Do you want to write the answer to a file?");
        
        for (int i = 0; i < n_choices; i++) {
            if (highlight == i + 1) {
                wattron(win, A_REVERSE);
            }
            print_centered_message(win, i + 4, choices[i]);
            wattroff(win, A_REVERSE);
        }
        
        int c = wgetch(win);
        switch (c) {
            case KEY_UP:
                highlight = (highlight == 1) ? n_choices : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight == n_choices) ? 1 : highlight + 1;
                break;
            case 10:  // Enter key
                choice = highlight;
                break;
        }
    }
    
    return (choice == 1) ? 2 : 1;
}

void start_interactive_mode(DataBase* database) {
    // Initialize ncurses
    initscr();
    clear();
    noecho();
    cbreak();
    
    // Create main window
    int height = 20;
    int width = 60;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;
    WINDOW* main_win = newwin(height, width, starty, startx);
    keypad(main_win, TRUE);
    
    // Initialize program state
    ProgramState state = {
        .database_populated = false
    };
    
    MenuState current_state = DATASET_SELECTION;
    bool first_run = true;
    
    while (current_state != EXIT) {
        switch (current_state) {
            case DATASET_SELECTION:
                if (handle_dataset_selection(main_win, database, &state)) {
                    current_state = QUERY_EXECUTION;
                } else {
                    current_state = EXIT;
                }
                break;
                
            case QUERY_EXECUTION:
                if (state.database_populated) {
                    wclear(main_win);
                    box(main_win, 0, 0);
                    wrefresh(main_win);
                    int mode = first_run ? ask_to_write_to_file(main_win) : 1;
                    first_run = false;
                    queries_worker(database, NULL, mode, main_win);
                } else {
                    current_state = DATASET_SELECTION;
                }
                break;
                
            default:
                current_state = EXIT;
                break;
        }
    }
    
    free_database(database);
    
    // Cleanup
    delwin(main_win);
    endwin();
}