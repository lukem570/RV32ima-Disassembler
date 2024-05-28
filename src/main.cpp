#include <stdio.h>
#include <cstring>
#include <fstream>

#include "instruction-decoder.hpp"

using namespace std;

enum class file_type {
    TXT,
    CSV,
};

int formatOutput(file_type, char*, char*);

int main(int argc, char *argv[]){

    char *input_file_name;
    char *output_file_name;
    file_type type; //defaults to txt

    //gets parameters
    for(int i = 0; i < argc; i++){
        if (argv[i][0] == '-'){
            switch (argv[i][1]){
            case 'i': input_file_name = argv[i + 1]; break;
            case 'o': output_file_name = argv[i + 1]; break;
            case 'f': 
                if(strcmp(argv[i + 1], "txt") == 0) { 
                    type = file_type::TXT;
                }else if (strcmp(argv[i + 1], "csv") == 0){
                    type = file_type::CSV;
                } else {
                    printf("invalid type\n");
                    return -1;
                } break;
            }
        }
    }

    if (!input_file_name || !output_file_name){
        printf("missing required parameters\n");
        return -1;
    }

    return formatOutput(type, input_file_name, output_file_name);
}

int formatOutput(file_type type, char* input_file_name, char* output_file_name){

    ifstream file;

    file.open("test/fibSeq.bin", std::ios::in|std::ios::binary);

    if(!file.is_open()){
        printf("error loading file");
        return -1;
    }

    file.seekg(0, ios::end);
   
    int file_size = file.tellg();
    int instruction;

    file.seekg(0, ios::beg);

    printf("%i\n", file_size);

    for(int i = 0; i < file_size; i += 4){
        file.read((char*)&instruction, sizeof(int));
        printf("%x\n", instruction);
    }

    file.close();

    return 0;
}