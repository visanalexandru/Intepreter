//
// Created by gvisan on 27.08.2020.
//

#ifndef INTERPRETER_OPCODE_H
#define INTERPRETER_OPCODE_H

#include <cstdint>

namespace VM {
    enum Opcode : uint8_t {
        LOAD_LITERAL,
        BINARY_ADD,
        BINARY_SUBTRACT,
        BINARY_MULTIPLY,
        BINARY_DIVIDE,
        BINARY_MODULUS,
        BINARY_EQUAL,
        BINARY_NEQUAL,
        BINARY_GREATER,
        BINARY_GREATEREQ,
        BINARY_LESS,
        BINARY_LESSEQ,
        UNARY_MINUS,
        UNARY_NOT,
        FUNCTION_CALL,
        JUMP_IF_FALSE,
        JUMP_IF_TRUE,
        JUMP,
        POP,
        LOAD_LOCAL,
        LOAD_GLOBAL,
        ASSIGN_LOCAL,
        ASSIGN_GLOBAL
    };

}


#endif //INTERPRETER_OPCODE_H
