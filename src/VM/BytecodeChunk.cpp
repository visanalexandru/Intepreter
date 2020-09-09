//
// Created by gvisan on 31.08.2020.
//

#include "BytecodeChunk.h"

namespace VM{
    uint8_t * BytecodeChunk::getData() {
        return &bytecode[0];
    }

    unsigned int BytecodeChunk::getBytecodeSize() const {
        return bytecode.size();
    }

    void BytecodeChunk::pushUInt(uint32_t to_push){
        bytecode.push_back(to_push & 0xffu);
        bytecode.push_back((to_push >> 8u) & 0xffu);
        bytecode.push_back((to_push >> 16u) & 0xffu);
        bytecode.push_back((to_push >> 24u) & 0xffu);
    }

    void BytecodeChunk::patchUInt(uint32_t to_patch, unsigned int index) {
        memcpy(&bytecode[index],&to_patch,4);
    }

    void BytecodeChunk::pushOpcode(Opcode opcode) {
        bytecode.push_back((uint8_t)opcode);
    }
}