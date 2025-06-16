#include "test.c"

// ./programa-testes ../../Dados-fase1/inputs_exemplo.txt ../../Dados-fase1/outputs_esperados

// ./programa-testes ../../fase2-small/small/dataset/com_erros ../../fase2-small/small/inputs-small.txt ../../fase2-small/small/outputs_esperados

int main(int argc, char* argv[]){

    if (argc != 4) {
        fprintf(stderr, "Wrong number of arguments.\n");
        return 1;
    }

    char* dataset_dir = argv[1];
    char* input_path = argv[2];
    char* expected_output_dir = argv[3];
    char* output_dir = "./resultados";

    run_tests(dataset_dir, input_path, expected_output_dir, output_dir);
    return 0;
}