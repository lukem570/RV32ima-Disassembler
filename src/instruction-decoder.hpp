#include <cstdint>


// https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf
enum class opcode {
    LUI          = 0b0110111,
    AUIPC        = 0b0010111,
    JAL          = 0b1101111,
    JALR         = 0b1100111,
    BRANCH       = 0b1100011,
    LOAD         = 0b0001111,
    STORE        = 0b0101111,
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
    SRLI         = 0b101,
    SRAI         = 0b101, //unique
};

enum class arithmetic_func {
    ADD          = 0b000,
    SUB          = 0b000, //unique
    SLL          = 0b001,
    SLT          = 0b010,
    SLTU         = 0b011,
    XOR          = 0b100,
    SRL          = 0b101,
    SRA          = 0b101, //unique
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
    ECALL        = 0b000,
    EBREAK       = 0b000, //unique
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

char *decodeInstruction(uint32_t instruction){

    return (char*)"hello";
}