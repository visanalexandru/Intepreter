//
// Created by gvisan on 31.08.2020.
//

#include "BytecodeChunk.h"

namespace VM{

    BytecodeChunk::BytecodeChunk():cursor(0) {

    }

    bool BytecodeChunk::reachedEnd() const {
        return cursor==bytecode.size();
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

    uint32_t BytecodeChunk::readUInt() {
        uint32_t a = bytecode[cursor];
        uint32_t b = bytecode[cursor+ 1] << 8u;
        uint32_t c = bytecode[cursor+ 2] << 16u;
        uint32_t d = bytecode[cursor+ 3] << 24u;

        cursor+= 4;

        return a | b | c | d;
    }

    void BytecodeChunk::patchUInt(uint32_t to_patch, unsigned int index) {
        bytecode[index] = to_patch & 0xffu;
        bytecode[index + 1] = (to_patch >> 8u) & 0xffu;
        bytecode[index + 2] = (to_patch >> 8u) & 0xffu;
        bytecode[index + 3] = (to_patch >> 8u) & 0xffu;
    }

    void BytecodeChunk::pushOpcode(Opcode opcode) {
        bytecode.push_back((uint8_t)opcode);
    }

    Opcode BytecodeChunk::readOpcode() {
        return (Opcode)bytecode[cursor++];
    }

    void BytecodeChunk::jump(unsigned location) {
        cursor=location;
    }

    unsigned int BytecodeChunk::getCursor() const {
        return cursor;
    }
}