#ifndef INTERACTIVE_QUERYING_H
#define INTERACTIVE_QUERYING_H

#include <ncurses.h>

/**
 * @brief Handles the execution of queries in an interactive ncurses window.
 *
 * This function displays a menu of queries that the user can select from. The user can navigate
 * through the menu using the arrow keys and select a query to execute by pressing the Enter key.
 * If the user selects the "Exit" option, the program will terminate.
 *
 * @param win A pointer to the ncurses window where the menu will be displayed.
 * @return A pointer to a string containing the result of the selected query.
 */
char* handle_query_execution(WINDOW* win);

/**
 * @brief Draws the interactive response on the given window.
 *
 * This function takes a window, a line, and a query answer, and draws the
 * interactive response on the specified window.
 *
 * @param window The window where the response will be drawn.
 * @param line The line to be displayed in the window.
 * @param query_answer The answer to the query that will be displayed.
 */
void draw_interactive_response(WINDOW* window,char* line,char* query_answer);

#endif