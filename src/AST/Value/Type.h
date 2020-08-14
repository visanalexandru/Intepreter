//
// Created by gvisan on 11.08.2020.
//

#ifndef INTERPRETER_TYPE_H
#define INTERPRETER_TYPE_H

#include<string>

namespace AST {

    enum class Type {
        Float,
        Int,
        String,
        None
    };

    /*Converts a type to a string for logging purposes*/
    inline std::string typeToString(Type type) {
        switch (type) {
            case Type::Int:
                return "Int";
            case Type::String:
                return "String";
            case Type::Float:
                return "Float";
            case Type::None:
                return "None";
        }
    }
}


#endif //INTERPRETER_TYPE_H
