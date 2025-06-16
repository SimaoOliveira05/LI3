#ifndef INTERACTIVE_UTILITIES_H
#define INTERACTIVE_UTILITIES_H

#include "ncurses.h"

/**
 * @brief Prints a centered message in a specified window.
 *
 * This function takes a window and prints a message centered at the specified
 * starting y-coordinate.
 *
 * @param win The window where the message will be printed.
 * @param starty The y-coordinate where the message will start.
 * @param message The message to be printed.
 */
void print_centered_message(WINDOW* win, int starty, const char* message);

#endif