#include "./data/database.h"
#include "./interactive/interactive.h"
#include <stdio.h>

int main(){
    DataBase* database = initialize_database();

    start_interactive_mode(database);

    return 0;
}