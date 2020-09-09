//
// Created by gvisan on 31.08.2020.
//

#ifndef INTERPRETER_BYTECODECHUNK_H
#define INTERPRETER_BYTECODECHUNK_H

#include "Opcode.h"
#include<vector>
#include<cstring>

namespace VM {


    class BytecodeChunk {

    private:
        std::vector<uint8_t> bytecode;

    public:
        unsigned getBytecodeSize() const;

        uint8_t* getData();

        void pushUInt(uint32_t to_push);

        void pushOpcode(Opcode opcode);

        void patchUInt(uint32_t to_patch, unsigned index);
    };
}


#endif //INTERPRETER_BYTECODECHUNK_H
