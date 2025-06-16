#include "./workers/batch.h"
#include "./data/database.h"
#include "./workers/queries_worker.h" 

#include <stdio.h>

int call_batch(char** argv){

    printf("Batch Called with: (%s)\n", argv[1]);
    char* path_to_data = argv[1];

    DataBase* database = initialize_database();

    populate_database(database, path_to_data, 0);

    queries_worker(database, argv[2], 0, NULL);

    free_database(database);

    return 0;
}
