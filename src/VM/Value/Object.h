//
// Created by gvisan on 03.09.2020.
//

#ifndef INTERPRETER_OBJECT_H
#define INTERPRETER_OBJECT_H
#include<string>
namespace VM{
    enum class ObjectType {
        String,
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
}


#endif //INTERPRETER_OBJECT_H
