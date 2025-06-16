#include "./workers/batch.h"
#include "./data/catalogs/catalogs_utils/liked_musics_list.h"

#include <stdio.h>

//INPUT Fase1: ./programa-principal ../../Dados-fase1/dataset/com_erros ../../Dados-fase1/inputs_exemplo.txt
//INPUT Fase2: ./programa-principal ../../Dados-fase2/small/dataset/com_erros ../../Dados-fase2/small/input.txt
//Eu tenho as pastas organizadas assim, mas se quiserdes mudai essa organização relativa da pasta de dados para uma padrão que sirva para todos


int main(int argc, char **argv){

    if (argc < 3) {

        fprintf(stderr, "Error: Missing arguments.\n");

    }else{

        call_batch(argv);

    }
    
    return 0;
}