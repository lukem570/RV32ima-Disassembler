#include <stdio.h>
#include <cstring>
#include <fstream>
#include <cstdint>
#include <sstream>
#include <iomanip>

#include "instruction-decoder.hpp"

using namespace std;

enum class file_type {
    TXT,
    CSV,
};

int formatOutput(file_type, char*, char*, bool, bool);

int main(int argc, char *argv[]){

    char *input_file_name;
    char *output_file_name;
    file_type type; // defaults to txt
    bool big_endian = false;
    bool log = false;

    // gets parameters
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
            case 'b': big_endian = true; 
            case 'l': log = true;
            }
        }
    }

    if (!input_file_name || !output_file_name){
        printf("missing required parameters\n");
        return -1;
    }

    delete argv;
    return formatOutput(type, input_file_name, output_file_name, big_endian, log); // adding a class for this might be ideal
}

int32_t sign_extend_to_32(int value, int num_bits) {
    int32_t sign_extend_mask = (1 << (num_bits - 1)) - 1;
    if (value & (1 << (num_bits - 1))) {
        sign_extend_mask |= ~((1 << num_bits) - 1);
    }
    return (int32_t)(value | sign_extend_mask);
}

int formatOutput(file_type type, char* input_file_name, char* output_file_name, bool big_endian, bool log){

    ifstream file;
    ofstream output(strcat(output_file_name, type == file_type::TXT ? ".txt" : ".csv"));

    file.open(input_file_name, ios::in|ios::binary);

    if(!file.is_open()){
        printf("error loading file");
        return -1;
    }

    if(!output.is_open()){
        printf("error creating file");
        return -1;
    }

    file.seekg(0, ios::end);
   
    int file_size = file.tellg();
    int instruction;

    file.seekg(0, ios::beg);

    // seems slow to add to the file each time and to read each time although i dont feel like implementing another way
    for(int i = 0; i < file_size; i += 0x4){
        file.read((char*)&instruction, sizeof(int));

        // manual conversion from little endian to big endian
        if(big_endian){
            instruction = ((instruction >> 24) & 0xff) |
                ((instruction << 8) & 0xff0000) |
                ((instruction >> 8) & 0xff00) |
                ((instruction << 24) & 0xff000000);
        }
        
        stringstream line;

        if(type == file_type::TXT){
            line
                << setfill('0') << setw(8) << i << "  " 
                << "0x" << setfill('0') << setw(8) << hex << i << "   " 
                << dec << setfill(' ') << setw(8) << decodeInstruction(instruction).c_str()
                << setfill(' ') << setw(5) << ((instruction >> 7) & 0b11111)
                << setfill(' ') << setw(3) << ((instruction >> 15) & 0b11111)
                << setfill(' ') << setw(3) << ((instruction >> 20) & 0b11111)
                << setfill(' ') << setw(10) << sign_extend_to_32((instruction >> 20), 12) //i type imm
                << setfill(' ') << setw(10) << sign_extend_to_32(((instruction >> 25) & 0b111111111111 << 7) | ((instruction >> 7) & 0b11111), 12) //s type imm
                << setfill(' ') << setw(10) << sign_extend_to_32((((instruction >> 31) & 0b1 << 12) | ((instruction >> 7) & 0b1 << 11) | ((instruction >> 25) & 0b11111111111 << 7) | ((instruction >> 8) & 0b1111)) << 1, 13) //b type imm
                << setfill(' ') << setw(10) << ((instruction >> 12) & 0xFFFFF) << 12 //u type imm
                << endl;
        } else if (type == file_type::CSV){

        }
        
        output << line.str();

        if (log){
            printf("%s", line.str().c_str());
        }
    }

    file.close();
    output.close();

    delete input_file_name, output_file_name;
    return 0;
}