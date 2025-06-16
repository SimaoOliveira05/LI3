#include <sys/resource.h>
#include <time.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include "./data/database.h"
#include "./workers/queries_worker.h"
#include "./data/catalogs/catalogs_utils/populate_genre_musics_catalog.h"
#include "./data/catalogs/catalogs_utils/determine_top_10.h"
#include "./workers/compare.c"

#define NUM_QUERIES 6

int run_tests(char* dataset_dir, char* input_path, char* expected_output_dir, char* result_path) {
    double total_time = 0;
    Error different_commands[100];
    int diff_count = 0;

    /* Initializing database and adding basic data */
    clock_t begin = clock();
    DataBase* database = initialize_database();
    int user_count = populate_database(database, dataset_dir, 1);
    clock_t end = clock();

    double initialize_database_elements_time = (double)(end - begin) / CLOCKS_PER_SEC;
    total_time += initialize_database_elements_time;

    clock_t query1_struct = clock();
    actualize_artist_group_participation(get_artists_catalog(database));
    clock_t end_query1_struct = clock();

    double query1_struct_time = (double)(end_query1_struct - query1_struct) / CLOCKS_PER_SEC;

    total_time += query1_struct_time;

    /* Creating struct for query2 */
    clock_t query2_struct = clock();
    transform_into_sorted_discography_array(get_artists_catalog(database));
    clock_t end_query2_struct = clock();

    double query2_struct_time = (double)(end_query2_struct - query2_struct) / CLOCKS_PER_SEC;
    total_time += query2_struct_time;

    /* Creating struct for query3 */
    clock_t query3_struct = clock();
    populate_genre_musics_catalog(database);
    clock_t end_query3_struct = clock();

    double query3_struct_time = (double)(end_query3_struct - query3_struct) / CLOCKS_PER_SEC;
    total_time += query3_struct_time;


    clock_t query4_struct = clock();
    calculate_top_10_per_week(get_historys_catalog(database));
    clock_t end_query4_struct = clock();

    double query4_struct_time = (double)(end_query4_struct - query4_struct) / CLOCKS_PER_SEC;
    total_time += query4_struct_time;

    clock_t query5_struct = clock();
    Recommender* recommender = create_and_populate_recommender(get_historys_catalog(database),user_count, get_genres_count(get_musics_catalog(database)),database);
    set_recommender(get_users_catalog(database),recommender);
    clock_t end_query5_struct = clock();

    double query5_struct_time = (double)(end_query5_struct - query5_struct) / CLOCKS_PER_SEC;
    total_time += query5_struct_time;

    /* Total initializing database time */
    double initialize_database_time = initialize_database_elements_time + query2_struct_time + query3_struct_time;

    /* Memory usage */
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);

    double querietimes[NUM_QUERIES] = {0};
    int calltimes[NUM_QUERIES] = {0};

    int command_counter = 0;

    char* path = input_path;
    FILE* fp = fopen(path, "r");

    if (!fp) {
        perror("Error");
        return 2;
    }

    char *line = NULL;
    size_t length = 0;

    printf("\n=========================================\n");
    printf("        STARTING QUERY PROCESSING        \n");
    printf("=========================================\n\n");

    while (getline(&line, &length, fp) != -1) {
        command_counter++;
        printf("🔄 Processing Query %d...\n", command_counter);

        clock_t begin_query = clock();
        int num = format_and_write_query_answer(command_counter, line, database, 0, NULL);
        clock_t end_query = clock();

        querietimes[num - 1] += (double)(end_query - begin_query) / CLOCKS_PER_SEC;
        calltimes[num - 1]++;
        Error linha = compare_files(result_path, expected_output_dir, command_counter);

        if (linha.differences > 0) {
            different_commands[diff_count] = linha;
            diff_count++;
        }
    }

    fclose(fp);
    free(line);

    printf("\n✅ Total Queries Processed: %d\n", command_counter);

    printf("\n=========================================\n");
    printf("        QUERY PROCESSING COMPLETED       \n");
    printf("=========================================\n");

    printf("\n==================================\n");
    printf("         TESTING RESULTS          \n");
    printf("==================================\n");

    printf("==================================\n");
    printf("       MEMORY & TIME SUMMARY      \n");
    printf("==================================\n\n");

    printf("🔧 Peak Memory Usage: %ld KB\n", r_usage.ru_maxrss);
    printf("📦 Elements Struct Creation Time: %.6f s\n", initialize_database_elements_time);
    printf("📊 Query 2 Struct Creation Time: %.6f s\n", query2_struct_time);
    printf("📊 Query 3 Struct Creation Time: %.6f s\n", query3_struct_time);
    printf("📊 Query 4 Struct Creation Time: %.6f s\n", query4_struct_time);
    printf("📊 Query 5 Struct Creation Time: %.6f s\n", query5_struct_time);
    printf("💾 Total Database Initialization Time: %.6f s\n", initialize_database_time);

    /* DataBase free Time */
    clock_t begin_free = clock();
    free_database(database);
    clock_t end_free = clock();

    double free_database_time = (double)(end_free - begin_free) / CLOCKS_PER_SEC;
    total_time += free_database_time;

    printf("🗑️  Free Database Time: %.6f s\n", free_database_time);
    printf("⏳ Total Time: %.6f s\n", total_time);

    printf("\n==================================\n");
    printf("         QUERY STATISTICS         \n");
    printf("==================================\n\n");

    for (int i = 0; i < NUM_QUERIES; i++) {
        total_time += querietimes[i];
        printf("⏱️  Average Query %d Run Time: %.6lf s\n", i + 1, querietimes[i] / calltimes[i]);
    }

    printf("\n");

    printf("==================================\n");
    printf("         DIFFERENT COMMANDS        \n");
    printf("==================================\n\n");

    // DEIXAR MAIS BONITO DEPOIS E CHECKAR SE FUNCIONA MESMO!
    if (diff_count == 0) {
        printf("✅ All outputs match expected results!\n");
    } else {
        printf("❌ %d commands have different outputs.\n", diff_count);
        for (int i = 0; i < diff_count; i++) {
            printf("🔍 Command %d has differences in lines: ", different_commands[i].file_number);
            if (different_commands[i].differences > 10) {
                printf("Tantos erros que nem vale a pena te dizer 😂\n");
            } else {
                for (int j = 0; j < different_commands[i].differences; j++) {
                    printf("%d ", different_commands[i].line_number[j]);
                }
                printf("\n");
            }
        }
    }
    return 0;
}

