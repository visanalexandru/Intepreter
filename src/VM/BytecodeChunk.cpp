//
// Created by gvisan on 31.08.2020.
//

#include "BytecodeChunk.h"

namespace VM{

    BytecodeChunk::BytecodeChunk():cursor(0),size(0) {

    }

    bool BytecodeChunk::reachedEnd() const {
        return cursor==size;
    }

    unsigned int BytecodeChunk::getBytecodeSize() const {
        return size;
    }

    void BytecodeChunk::pushUInt(uint32_t to_push){
        bytecode.push_back(to_push & 0xffu);
        bytecode.push_back((to_push >> 8u) & 0xffu);
        bytecode.push_back((to_push >> 16u) & 0xffu);
        bytecode.push_back((to_push >> 24u) & 0xffu);
        size+=4;
    }

    uint32_t BytecodeChunk::readUInt() {
        uint32_t result;
        memcpy(&result,&bytecode[cursor],4);
        cursor+= 4;
        return result;
    }

    void BytecodeChunk::patchUInt(uint32_t to_patch, unsigned int index) {
        memcpy(&bytecode[index],&to_patch,4);
    }

    void BytecodeChunk::pushOpcode(Opcode opcode) {
        bytecode.push_back((uint8_t)opcode);
        size+=1;
    }

    uint8_t BytecodeChunk::readByte() {
        return bytecode[cursor++];
    }

    void BytecodeChunk::jump(unsigned location) {
        cursor=location;
    }

    unsigned int BytecodeChunk::getCursor() const {
        return cursor;
    }
}