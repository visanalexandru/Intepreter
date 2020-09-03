//
// Created by gvisan on 11.08.2020.
//

#ifndef INTERPRETER_TYPE_H
#define INTERPRETER_TYPE_H

#include<string>

namespace VM{

    enum class ValueType {
        Float,
        Int,
        Bool,
        None
    };


    /*Converts a type to a string for logging purposes*/
    inline std::string typeToString(ValueType type) {
        switch (type) {
            case ValueType::Int:
                return "Int";
            case ValueType::Float:
                return "Float";
            case ValueType::None:
                return "None";
            case ValueType::Bool:
                return "Bool";
        }
    }
}


#endif //INTERPRETER_TYPE_H
