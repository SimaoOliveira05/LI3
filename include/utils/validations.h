#ifndef VALIDATIONS_H
#define VALIDATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Sees if the date is valid.
 * 
 * @param date mm/dd/yyyy.
 * @return int 0 if the date is valid, 1 otherwise.
 */
int date_validation(char* date);

/**
 * @brief Sees if the time is valid.
 * 
 * @param time hh:mm:ss.
 * @return int 0 if the time is valid, 1 otherwise.
 */
int time_validation(char* time);

/**
 * @brief Sees if the email is valid.
 * 
 * @param email The email.
 * @return int 0 if the email is valid, 1 otherwise.
 */
int email_validation(char* email);

/**
 * @brief Sees if the subscription type is valid.
 * 
 * @param type The subscription type.
 * @return int 0 if the subscription type is valid, 1 otherwise.
 */
int subscription_type_validation(char* type);

/**
 * @brief Sees if the artist id is valid.
 * 
 * @param id_artist The artist id.
 * @return int 0 if the artist id is valid, 1 otherwise.
 */
int artist_id_validation(char* id_constituint, char* type);

/**
 * @brief Sees if the history platform is valid.
 * 
 * @param platform The history platform.
 * @return int 1 if the history platform is valid, 0 otherwise.
 */
int platform_validation(char* platform);

/**
 * @brief Sees if the artist type is valid.
 * 
 * @param type The type of the artist
 * @return int 1 if it is valid, 0 otherwise.
 */
int type_validation(char* type);

#endif