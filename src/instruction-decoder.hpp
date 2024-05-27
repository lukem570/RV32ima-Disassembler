
// https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf
enum class opcode {
    LUI,
    AUIPC,
    BRANCH,
    LOAD,
    STORE,
    IMMEDIATE,
    ARITHMETIC,
    FENCE,
    SYSTEM,
    ATOMIC,
};

enum class branch_func {
    BEQ,
    BNE,
    BLT,
    BGE,
    BLTU,
    BGUE,
};

enum class load_func {
    LB,
    LH,
    LW,
    LBU,
    LHU,
};

enum class store_func {
    SB,
    SH,
    SW,
};

enum class immediate_func {
    ADDI,
    SLTI,
    SLTIU,
    XORI,
    ORI,
    ANDI,
    SLLI,
    SRLI,
    SRAI, //unique
};

enum class arithmetic_func {
    ADD,
    SUB, //unique
    SLL,
    SLT,
    SLTU,
    XOR,
    SRL,
    SRA,
    OR,
    AND,
};

enum class fence_func {
    FENCE,
    FENCEI,
};

enum class system_func {
    ECALL,
    EBREAK, //unique
    CSRRW,
    CSRRS,
    CSRRC,
    CSRRWI,
    CSRRSI,
    CSRRCI
};