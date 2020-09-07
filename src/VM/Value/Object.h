//
// Created by gvisan on 03.09.2020.
//

#ifndef INTERPRETER_OBJECT_H
#define INTERPRETER_OBJECT_H

#include<string>
#include "VM/BytecodeChunk.h"

namespace VM {
    class Value;

    struct Object {
        Object *next;//the object that was allocated after this object
        Object *previous;//the object that was allocated before this object
        Object() : previous(nullptr), next(nullptr) {

        }

        virtual ~Object() = default;
    };

    struct StringObj : public Object {
        std::string data;

        explicit StringObj(std::string str) : data(std::move(str)) {

        }
    };

    struct NativeFunctionObj : public Object {
        std::string name;
        unsigned arity;

        Value (*data)(Value *);

        NativeFunctionObj(std::string id, unsigned params, Value(*func)(Value *)) :
                name(std::move(id)),
                arity(params),
                data(func) {

        }

    };

    struct DefinedFunctionObj : public Object {
        std::string name;
        unsigned arity;
        BytecodeChunk bytecode;


        DefinedFunctionObj(std::string id, unsigned params, BytecodeChunk chunk) : name(std::move(id)),
                                                                                   arity(params),
                                                                                   bytecode(std::move(chunk)) {

        }
    };

}


#endif //INTERPRETER_OBJECT_H
