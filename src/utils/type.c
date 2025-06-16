#include <stdlib.h>
#include <string.h>
#include "./utils/type.h"

char* convert_type(short int type){
    if (type == 0)
        return "individual";
    else
        return "group";
}