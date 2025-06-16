#include "./interactive/interactive_querying.h"
#include "./interactive/interactive_utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* inputs_interativo_Query1(WINDOW* window) {
    int highlight = 1;
    int choice = 0;
    int c;
    char id[256];

    char* choices[] = {
        "User",
        "Artist",
        "Go Back"
    };
    int n_choices = sizeof(choices) / sizeof(char*);

    int height = 20;
    int width = 60;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;

    wclear(window);
    WINDOW* menu_win = newwin(height, width, starty, startx);
    if (menu_win == NULL) {
        perror("Error creating window");
        return NULL;
    }
    keypad(menu_win, TRUE);
    print_centered_message(window, 0, "Use arrow keys to go up and down, Press enter to select a choice");
    box(menu_win, 0, 0);
    for (int i = 0; i < n_choices; ++i) {
        if (highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
        }
        print_centered_message(menu_win, i + 1, choices[i]);
        if (highlight == i + 1) {
            wattroff(menu_win, A_REVERSE);
        }
    }
    wrefresh(menu_win);

    while (1) {
        c = wgetch(menu_win);
        switch (c) {
            case KEY_UP:
                highlight = (highlight == 1) ? n_choices : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight == n_choices) ? 1 : highlight + 1;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                break;
        }
        for (int i = 0; i < n_choices; ++i) {
            if (highlight == i + 1) {
                wattron(menu_win, A_REVERSE);
            }
            print_centered_message(menu_win, i + 1, choices[i]);
            if (highlight == i + 1) {
                wattroff(menu_win, A_REVERSE);
            }
        }
        wrefresh(menu_win);
        if (choice != 0) {
            break;
        }
    }

    if (choice == 3) {  // Exit
        delwin(menu_win);
        return NULL;
    }

    // Limpar a janela e solicitar o ID
    wclear(menu_win);
    box(menu_win, 0, 0);
    echo();
    if (choice == 1) {
        wattron(menu_win, A_REVERSE);
        print_centered_message(menu_win, 1, "User");
        wattroff(menu_win, A_REVERSE);
    } else if (choice == 2) {
        wattron(menu_win, A_REVERSE);
        print_centered_message(menu_win, 2, "Artist");
        wattroff(menu_win, A_REVERSE);
    }
    print_centered_message(menu_win, height / 2 - 1, "Enter the ID: ");
    wrefresh(menu_win);
    wgetnstr(menu_win, id, sizeof(id) - 1);  // Use wgetnstr para evitar buffer overflow
    noecho();

    // Ajustar o tamanho do buffer result para garantir espaço suficiente
    size_t result_size = strlen(id) + 4;  // 4 para "1 U" ou "1 A" e '\0'
    char* result = malloc(result_size);
    if (result == NULL) {
        perror("Error allocating memory");
        delwin(menu_win);
        return NULL;
    }
    if (choice == 1) {
        snprintf(result, result_size, "1 U%s", id);
    } else if (choice == 2) {
        snprintf(result, result_size, "1 A%s", id);
    }
    delwin(menu_win);
    return result;
}

char* inputs_interativo_Query2(WINDOW* window){
    int highlight = 1;
    int choice = 0;
    int c;
    char num_artists[256];
    char country[256] = "";

    wclear(window);
    box(window, 0, 0);  // Keep the borders
    echo();
    print_centered_message(window, 2, "Enter the number of artists: ");
    wrefresh(window);
    wgetstr(window, num_artists);
    noecho();

    char* choices[] = {
        "Yes",
        "No"
    };
    int n_choices = sizeof(choices) / sizeof(char*);

    print_centered_message(window, 4, "Do you want to add a country filter?");
    for (int i = 0; i < n_choices; ++i) {
        if (highlight == i + 1) {
            wattron(window, A_REVERSE);
        }
        print_centered_message(window, i + 6, choices[i]); // Adjusted to center vertically
        if (highlight == i + 1) {
            wattroff(window, A_REVERSE);
        }
    }
    wrefresh(window);

    while (1) {
        c = wgetch(window);
        switch (c) {
            case KEY_UP:
                highlight = (highlight == 1) ? n_choices : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight == n_choices) ? 1 : highlight + 1;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                break;
        }
        for (int i = 0; i < n_choices; ++i) {
            if (highlight == i + 1) {
                wattron(window, A_REVERSE);
            }
            print_centered_message(window, i + 6, choices[i]); // Adjusted to center vertically
            if (highlight == i + 1) {
                wattroff(window, A_REVERSE);
            }
        }
        wrefresh(window);
        if (choice != 0) {
            break;
        }
    }

    if (choice == 1) {  // Yes
        echo();
        print_centered_message(window, 8, "Enter the country: ");
        wrefresh(window);
        wgetstr(window, country);
        noecho();
    }

    // Adjust the size of the result buffer to ensure enough space
    size_t result_size = strlen(num_artists) + strlen(country) + 10;
    char* result = malloc(result_size);
    if (choice == 1) {
        snprintf(result, result_size, "2 %s %s", num_artists, country);
    } else {
        snprintf(result, result_size, "2 %s", num_artists);
    }

    wclear(window);  // Clear the main window after use
    wrefresh(window);
    return result;
}


char* inputs_interativo_Query3(WINDOW* window) {
    char min_age[256];
    char max_age[256];

    // Limpar a janela mantendo as bordas
    werase(window);
    box(window, 0, 0);
    wrefresh(window);

    // Perguntar a idade mínima
    echo();
    print_centered_message(window, 2, "Enter the minimum age: ");
    wgetstr(window, min_age);
    noecho();

    // Perguntar a idade máxima
    echo();
    print_centered_message(window, 4, "Enter the maximum age: ");
    wgetstr(window, max_age);
    noecho();

    // Construir a string no formato desejado
    size_t result_size = strlen(min_age) + strlen(max_age) + 4; // 4 for "3 ", " ", and '\0'
    char* result = malloc(result_size);
    snprintf(result, result_size, "3 %s %s", min_age, max_age);

    return result;
}


char* inputs_interativo_Query4(WINDOW* window){
    char start_date[256];
    char end_date[256];

    // Limpar a janela mantendo as bordas
    wclear(window);
    box(window, 0, 0);

    // Perguntar a data de início
    echo();
    print_centered_message(window, 2, "Enter the start date (YYYY/MM/DD): ");
    mvwgetstr(window, 3, (getmaxx(window) - 20) / 2, start_date);
    noecho();

    // Perguntar a data de término
    echo();
    print_centered_message(window, 6, "Enter the end date (YYYY/MM/DD): ");
    mvwgetstr(window, 7, (getmaxx(window) - 20) / 2, end_date);
    noecho();

    // Ajustar o tamanho do buffer result para garantir espaço suficiente
    size_t result_size = strlen(start_date) + strlen(end_date) + 10;
    char* result = malloc(result_size);
    snprintf(result, result_size, "4 %s %s", start_date, end_date);

    return result;
}

char* inputs_interativo_Query5(WINDOW* window) {
    char user_id[256];
    char num_users[256];

    // Limpar a janela mantendo as bordas
    wclear(window);
    box(window, 0, 0);
    wrefresh(window);

    // Perguntar o ID do usuário
    echo();
    print_centered_message(window, 2, "Enter the user ID: ");
    mvwgetstr(window, 3, (getmaxx(window) - 20) / 2, user_id);
    noecho();

    // Adicionar o prefixo "U" ao ID do usuário
    char user_id_with_prefix[258]; // 256 + 1 (U) + 1 (\0)
    snprintf(user_id_with_prefix, sizeof(user_id_with_prefix), "U%s", user_id);

    // Perguntar o número de usuários
    echo();
    print_centered_message(window, 5, "Enter the number of users: ");
    mvwgetstr(window, 6, (getmaxx(window) - 20) / 2, num_users);
    noecho();

    // Construir a string no formato desejado
    size_t result_size = strlen(user_id_with_prefix) + strlen(num_users) + 10;
    char* result = malloc(result_size);
    snprintf(result, result_size, "5 %s %s", user_id_with_prefix, num_users);

    // Adicionar mensagem de depuração
    printf("Query 5 Result: %s\n", result);

    return result;
}


char* inputs_interativo_Query6(WINDOW* window) {
    char user_id[256];
    char year[256];
    char num_artists[256] = "";

    // Clear the main window but keep the borders
    werase(window);
    box(window, 0, 0);
    wrefresh(window);

    // Perguntar o ID do usuário
    echo();
    print_centered_message(window, 2, "Enter the user ID: ");
    wgetstr(window, user_id);
    noecho();

    // Adicionar o prefixo "U" ao ID do usuário
    char user_id_with_prefix[258]; // 256 + 1 (U) + 1 (\0)
    snprintf(user_id_with_prefix, sizeof(user_id_with_prefix), "U%s", user_id);

    // Perguntar o ano
    echo();
    print_centered_message(window, 4, "Enter the year: ");
    wgetstr(window, year);
    noecho();

    // Perguntar se deseja imprimir quantos dos artistas mais populares
    char* choices[] = {
        "Yes",
        "No"
    };
    int n_choices = sizeof(choices) / sizeof(char*);

    int highlight = 1;
    int choice = 0;
    int c;

    print_centered_message(window, 6, "Do you want to print how many of the top artists?");
    for (int i = 0; i < n_choices; ++i) {
        int len = strlen(choices[i]);
        int startx = (60 - len) / 2;
        if (highlight == i + 1) {
            wattron(window, A_REVERSE);
            mvwprintw(window, 8 + i, startx, "%s", choices[i]);
            wattroff(window, A_REVERSE);
        } else {
            mvwprintw(window, 8 + i, startx, "%s", choices[i]);
        }
    }
    wrefresh(window);

    while (1) {
        c = wgetch(window);
        switch (c) {
            case KEY_UP:
                if (highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == n_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                break;
        }
        for (int i = 0; i < n_choices; ++i) {
            int len = strlen(choices[i]);
            int startx = (60 - len) / 2;
            if (highlight == i + 1) {
                wattron(window, A_REVERSE);
                mvwprintw(window, 8 + i, startx, "%s", choices[i]);
                wattroff(window, A_REVERSE);
            } else {
                mvwprintw(window, 8 + i, startx, "%s", choices[i]);
            }
        }
        wrefresh(window);
        if (choice != 0) {
            break;
        }
    }

    if (choice == 1) {  // Yes
        echo();
        print_centered_message(window, 10, "Enter the number of top artists: ");
        wgetstr(window, num_artists);
        noecho();
    }

    // Construir a string no formato desejado
    size_t result_size = strlen(user_id_with_prefix) + strlen(year) + strlen(num_artists) + 10;
    char* result = malloc(result_size);
    if (choice == 1) {
        snprintf(result, result_size, "6 %s %s %s", user_id_with_prefix, year, num_artists);
    } else {
        snprintf(result, result_size, "6 %s %s", user_id_with_prefix, year);
    }

    return result;
}


char* handle_query_execution(WINDOW* win) {
    wclear(win);
    box(win, 0, 0);
    
    char* choices[] = {
        "Query 1",
        "Query 2",
        "Query 3",
        "Query 4",
        "Query 5",
        "Query 6",
        "Exit"
    };
    int n_choices = 7;
    int highlight = 1;
    int choice = 0;
    
    while (choice == 0) {
        print_centered_message(win, 2, "Select Query to Execute:");
        
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
    
    if (choice == 7) {  // Go back
        endwin();  // End ncurses mode
        exit(0);   // Exit the program
    }
    
    char* line = NULL;

    switch (choice) {
        case 1:
            line = inputs_interativo_Query1(win);
            break;
        case 2:
            line = inputs_interativo_Query2(win);
            break;
        case 3:
            line = inputs_interativo_Query3(win);
            break;
        case 4:
            line = inputs_interativo_Query4(win);
            break;
        case 5:
            line = inputs_interativo_Query5(win);
            break;
        case 6:
            line = inputs_interativo_Query6(win);  
            break;
    }
    return line;
}

int find_largest_element(int arr[],int n){
    int max = arr[0];
    int index = 0;
    for(int i = 1; i < n; i++){
        if(arr[i] > max){
            index = i;
            max = arr[i];
        }
    }
    return index;
}

void draw_interactive_response(WINDOW* window, char* line, char* query_answer) {
    wclear(window);
    box(window, 0, 0);
    print_centered_message(window, 2, "Query:");
    print_centered_message(window, 3, line);
    print_centered_message(window, 5, "Response:");

    // Split the query_answer into lines and print each line
    char* token = strtok(query_answer, "\n");
    int line_num = 6;
    int max_lines = getmaxy(window) - 3; // Reserve space for borders and messages

    while (token != NULL) {
        if (line_num >= max_lines) {
            print_centered_message(window, line_num, "Output too large for terminal...");
            break;
        }
        print_centered_message(window, line_num++, token);
        token = strtok(NULL, "\n");
    }

    print_centered_message(window, max_lines, "Press any key to continue...");
    wrefresh(window);
    wgetch(window);
}