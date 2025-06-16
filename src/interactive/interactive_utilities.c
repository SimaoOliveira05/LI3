#include "./interactive/interactive_utilities.h"
#include <string.h>

void print_centered_message(WINDOW* win, int starty, const char* message) {
    int width;
    getmaxyx(win, width, width);
    int len = strlen(message);
    int startx = (width - len) / 2;
    mvwprintw(win, starty, startx, "%s", message);
    wrefresh(win);
}