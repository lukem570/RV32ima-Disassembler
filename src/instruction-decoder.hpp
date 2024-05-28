#include <cstdint>
#include <stdio.h>
using namespace std;
//kinda trading size for readability in this file

// https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf
enum class opcode {
    LUI          = 0b0110111,
    AUIPC        = 0b0010111,
    JAL          = 0b1101111,
    JALR         = 0b1100111,
    BRANCH       = 0b1100011,
    LOAD         = 0b0000011,
    STORE        = 0b0100011,
    IMMEDIATE    = 0b0010011,
    ARITHMETIC   = 0b0110011,
    FENCE        = 0b0001111,
    SYSTEM       = 0b1110011,
    ATOMIC       = 0b0101111,
};

enum class branch_func {
    BEQ          = 0b000,
    BNE          = 0b001,
    BLT          = 0b100,
    BGE          = 0b101,
    BLTU         = 0b110,
    BGUE         = 0b111,
};

enum class load_func {
    LB           = 0b000,
    LH           = 0b001,
    LW           = 0b010,
    LBU          = 0b100,
    LHU          = 0b101,
};

enum class store_func {
    SB           = 0b000,
    SH           = 0b001,
    SW           = 0b010,
};

enum class immediate_func {
    ADDI         = 0b000,
    SLTI         = 0b010,
    SLTIU        = 0b011,
    XORI         = 0b100,
    ORI          = 0b110,
    ANDI         = 0b111,
    SLLI         = 0b001,
    SRLI         = 0b101, // SRAI
};

enum class arithmetic_func {
    ADD          = 0b000, // SUB
    SLL          = 0b001,
    SLT          = 0b010,
    SLTU         = 0b011,
    XOR          = 0b100,
    SRL          = 0b101, // SRA
    OR           = 0b110,
    AND          = 0b111,
    //RV32M
    MUL          = 0b000, 
    MULH         = 0b001,
    MULHSU       = 0b010,
    MULHU        = 0b011,
    DIV          = 0b100,
    DIVU         = 0b101,
    REM          = 0b110,
    REMU         = 0b111,
};

enum class fence_func {
    FENCE        = 0b000,
    FENCEI       = 0b001,
};

enum class system_func {
    ECALL        = 0b000, //EBREAK
    CSRRW        = 0b001,
    CSRRS        = 0b010,
    CSRRC        = 0b011,
    CSRRWI       = 0b101,
    CSRRSI       = 0b110,
    CSRRCI       = 0b111,
};

enum class atomic_func {
    LR           = 0b00010,
    SC           = 0b00011,
    AMOSWAP      = 0b00001,
    AMOADD       = 0b00000,
    AMOXOR       = 0b00100,
    AMOAND       = 0b01100,
    AMOOR        = 0b01000,
    AMOMIN       = 0b10000,
    AMOMAX       = 0b10100,
    AMOMINU      = 0b11000,
    AMOMAXU      = 0b11100,
};

string decodeInstruction(uint32_t instruction){
    opcode instruction_opcode = (opcode)(instruction & 0b1111111);

    switch (instruction_opcode){
    case opcode::LUI: return "LUI"; 
    case opcode::AUIPC: return "AUIPC";
    case opcode::JAL: return "JAL";
    case opcode::JALR: return "JALR";
    case opcode::BRANCH: {
        branch_func branch = (branch_func)((instruction & 0b111000000000000) >> 12);
        switch (branch){
        case branch_func::BEQ: return "BEQ";
        case branch_func::BNE: return "BNE";
        case branch_func::BLT: return "BLT";
        case branch_func::BGE: return "BGE";
        case branch_func::BLTU: return "BLTU";
        case branch_func::BGUE: return "BGUE";
        default: return "_";
        }
    }
    case opcode::LOAD:{
        load_func load = (load_func)((instruction & 0b111000000000000) >> 12);
        switch (load){
        case load_func::LB: return "LB";
        case load_func::LH: return "LH";
        case load_func::LW: return "LW";
        case load_func::LBU: return "LBU";
        case load_func::LHU: return "LHU";
        default: return "_";
        }
    }
    case opcode::STORE:{
        store_func store = (store_func)((instruction & 0b111000000000000) >> 12);
        switch (store){
        case store_func::SB: return "SB";
        case store_func::SH: return "SH";
        case store_func::SW: return "SW";
        default: return "_";
        }
    }
    case opcode::IMMEDIATE:{
        immediate_func immediate = (immediate_func)((instruction & 0b111000000000000) >> 12);
        switch (immediate){
        case immediate_func::ADDI: return "ADDI";
        case immediate_func::SLTI: return "SLTI";
        case immediate_func::SLTIU: return "SLTIU";
        case immediate_func::XORI: return "XORI";
        case immediate_func::ORI: return "ORI";
        case immediate_func::ANDI: return "ANDI";
        case immediate_func::SLLI: return "SLLI";
        case immediate_func::SRLI: return (instruction & 0x40000000) ? "SRAI" : "SRLI";
        default: return "_";
        }
    }
    case opcode::ARITHMETIC:{
        arithmetic_func arithmetic = (arithmetic_func)((instruction & 0b111000000000000) >> 12);
        if(instruction & 0x02000000){ //RV32M
            switch (arithmetic){
            case arithmetic_func::MUL: return "MUL";
            case arithmetic_func::MULH: return "MULH";
            case arithmetic_func::MULHSU: return "MULHSU";
            case arithmetic_func::MULHU: return "MULHU";
            case arithmetic_func::DIV: return "DIV";
            case arithmetic_func::DIVU: return "DIVU";
            case arithmetic_func::REM: return "REM";
            case arithmetic_func::REMU: return "REMU";
            default: return "_";
            }
        }else{ //RV32I
            switch (arithmetic){
            case arithmetic_func::ADD: return (instruction & 0x40000000) ? "SUB" : "ADD";
            case arithmetic_func::SLL: return "SLL";
            case arithmetic_func::SLT: return "SLT";
            case arithmetic_func::SLTU: return "SLTU";
            case arithmetic_func::XOR: return "XOR";
            case arithmetic_func::SRL: return (instruction & 0x40000000) ? "SRA" : "SRL";
            case arithmetic_func::OR: return "OR";
            case arithmetic_func::AND: return "AND";
            default: return "_";
            }
        }
    }
    case opcode::FENCE:{
        fence_func fence = (fence_func)((instruction & 0b111000000000000) >> 12);
        switch (fence){
        case fence_func::FENCE: return "FENCE";
        case fence_func::FENCEI: return "FENCE.I";
        default: return "_";
        }
    }
    case opcode::SYSTEM:{
        system_func system = (system_func)((instruction & 0b111000000000000) >> 12);
        switch (system){
        case system_func::ECALL: return (instruction & 0x40000000) ? "EBREAK" : "ECALL";
        case system_func::CSRRW: return "CSRRW";
        case system_func::CSRRS: return "CSRRS";
        case system_func::CSRRC: return "CSRRC";
        case system_func::CSRRWI: return "CSRRWI";
        case system_func::CSRRSI: return "CSRRSI";
        case system_func::CSRRCI: return "CSRRCI";
        default: return "_";
        }
    }
    case opcode::ATOMIC:{
        atomic_func atomic = (atomic_func)((instruction & 0xf8000000) >> 27);
        switch (atomic){
        case atomic_func::LR: return "LR.W";
        case atomic_func::SC: return "SC.W";
        case atomic_func::AMOSWAP: return "AMOSWAP.W";
        case atomic_func::AMOADD: return "AMOADD.W";
        case atomic_func::AMOXOR: return "AMOXOR.W";
        case atomic_func::AMOAND: return "AMOAND.W";
        case atomic_func::AMOOR: return "AMOOR.W";
        case atomic_func::AMOMIN: return "AMOMIN.W";
        case atomic_func::AMOMAX: return "AMOMAX.W";
        case atomic_func::AMOMINU: return "AMOMINU.W";
        case atomic_func::AMOMAXU: return "AMOMAXU.W";
        default: return "_";
        }
    }
    default: return "_";
    }
}