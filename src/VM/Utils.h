//
// Created by gvisan on 09.09.2020.
//

#ifndef INTERPRETER_UTILS_H
#define INTERPRETER_UTILS_H

#include<cstdint>

namespace VM {

    inline uint8_t readByte(const uint8_t *data, unsigned &cursor) {
        uint8_t to_return=*(data+cursor);
        cursor++;
        return to_return;
    }

    inline uint32_t readUInt(const uint8_t*data,unsigned&cursor){
        uint32_t to_return =*(uint32_t*)(data+cursor);
        cursor+=4;
        return to_return;
    }
}


#endif //INTERPRETER_UTILS_H
