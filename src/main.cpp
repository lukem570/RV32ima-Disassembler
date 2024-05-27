#include <stdio.h>
#include <cstring>
#include <fstream>

#include "instruction-decoder.hpp"

using namespace std;

enum class file_type {
    TXT,
    CSV,
};

void formatOutput(file_type, char*, char*);

int main(int argc, char *argv[]){

    char *input_file_name;
    char *output_file_name;
    file_type type; //defaults to txt

    //gets parameters
    for(int i = 0; i < argc; i++){
        if (argv[i][0] == '-'){
            switch (argv[i][1])
            {
            case 'i': input_file_name = argv[i + 1]; break;
            case 'o': output_file_name = argv[i + 1]; break;
            case 'f': 
                if(strcmp(argv[i + 1], "txt") == 0) { 
                    type = file_type::TXT;
                }else if (strcmp(argv[i + 1], "csv") == 0){
                    type = file_type::CSV;
                } else {
                    printf("invalid type\n");
                } break;
            }
        }
    }

    if (!input_file_name || !output_file_name){
        printf("missing required parameters\n");
    }

    formatOutput(type, input_file_name, output_file_name);

    return 0;
}

void formatOutput(file_type type, char* input_file_name, char* output_file_name){

    ifstream file;

    file.open(input_file_name, std::ios::in|std::ios::binary);

    for(int i = 0; i < file.tellg() / 4; i++){
        
    }
}