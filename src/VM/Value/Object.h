//
// Created by gvisan on 03.09.2020.
//

#ifndef INTERPRETER_OBJECT_H
#define INTERPRETER_OBJECT_H
#include<string>
namespace VM{
    class Value;
    enum class ObjectType {
        String,
        NativeFunction
    };

    struct Object {
        ObjectType type;
        Object *next;//the object that was allocated after this object
        Object *previous;//the object that was allocated before this object
    };

    struct StringObj {
        Object header;
        std::string data;
    };

    struct NativeFunctionObj{
        Object header;
        unsigned arity;
        Value(*data)(Value*);
    };
}


#endif //INTERPRETER_OBJECT_H
