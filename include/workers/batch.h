#ifndef BATCH_H
#define BATCH_H

/**
 * @brief Executes a batch process using the provided arguments.
 * 
 * This function initializes a database, populates it with data from a specified path,
 * processes queries, and then frees the database resources. It takes an array of 
 * arguments where the first argument is the path to the data and the second argument 
 * is the path to the queries.
 * 
 * @param argv Array of arguments. 
 *             argv[1] should be the path to the data.
 *             argv[2] should be the path to the queries.
 * @return int Returns 0 upon successful execution.
 */
int call_batch(char** argv);

#endif