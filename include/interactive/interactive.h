#ifndef INTERACTIVE_H
#define INTERACTIVE_H

#include "./data/database.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct programstate ProgramState;
/**
 * @brief Checks if the given path is a valid directory.
 *
 * This function verifies whether the specified path points to a valid directory.
 *
 * @param path The path to the directory to be checked.
 * @return int Returns 1 if the path is a valid directory, 0 otherwise.
 */
int is_valid_directory(const char* path);

/**
 * @brief Checks if the dataset at the given path is valid.
 *
 * This function verifies the validity of the dataset located at the specified path.
 *
 * @param path The file path to the dataset.
 * @return int Returns 1 if the dataset is valid, 0 otherwise.
 */
int is_valid_dataset(const char* path);

/**
 * @brief Removes quotes from the given string and prints it.
 *
 * This function removes any quotes from the input string and prints the resulting string.
 *
 * @param str The input string from which quotes will be removed.
 */
void remove_quotes_Nprint(char* str);

/**
 * @brief Handles the selection of the default dataset.
 *
 * This function manages the process of selecting the default dataset
 * within the interactive mode.
 *
 * @param win The window where the selection process is displayed.
 * @param database The database object where the dataset will be loaded.
 * @param state The current state of the program.
 * @return bool Returns true if the default dataset is successfully selected, false otherwise.
 */
/**
 * @brief Handles the selection of the default dataset in the interactive window.
 *
 * This function manages the process of selecting the default dataset within the
 * provided window, updating the database and program state accordingly.
 *
 * @param win The window where the selection is made.
 * @param database The database to be updated based on the selection.
 * @param state The current state of the program to be modified.
 * @return true if the selection was successful, false otherwise.
 */
bool handle_default_dataset_selection(WINDOW* win, DataBase* database, ProgramState* state);

/**
 * @brief Handles the selection of a dataset in the interactive window.
 *
 * This function manages the process of selecting a dataset within the
 * provided window, updating the database and program state accordingly.
 *
 * @param win The window where the selection is made.
 * @param database The database to be updated based on the selection.
 * @param state The current state of the program to be modified.
 * @return true if the selection was successful, false otherwise.
 */
bool handle_dataset_selection(WINDOW* win, DataBase* database, ProgramState* state);
/**
 * @brief Starts the interactive mode.
 *
 * This function initiates the interactive mode, allowing the user to interact
 * with the database through a user interface.
 *
 * @param database The database object to be used in the interactive mode.
 */
void start_interactive_mode(DataBase* database);

#endif 