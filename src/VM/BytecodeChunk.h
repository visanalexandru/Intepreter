//
// Created by gvisan on 31.08.2020.
//

#ifndef INTERPRETER_BYTECODECHUNK_H
#define INTERPRETER_BYTECODECHUNK_H

#include "Opcode.h"
#include<vector>

namespace VM {


    class BytecodeChunk {

    private:
        std::vector<uint8_t> bytecode;

        unsigned cursor;

    public:
        BytecodeChunk();

        bool reachedEnd() const;

        unsigned getBytecodeSize() const;

        void pushUInt(uint32_t to_push);

        void pushOpcode(Opcode opcode);

        void patchUInt(uint32_t to_patch, unsigned index);

        uint32_t readUInt();

        Opcode readOpcode();

        void jump(unsigned location);

        unsigned getCursor() const;
    };
}


#endif //INTERPRETER_BYTECODECHUNK_H
