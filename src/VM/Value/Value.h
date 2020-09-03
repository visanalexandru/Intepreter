//
// Created by gvisan on 10.08.2020.
//

#ifndef INTERPRETER_VALUE_H
#define INTERPRETER_VALUE_H

#include<string>
#include<stdexcept>
#include"Type.h"

namespace VM{
    /*This class represents a value in the interpreted program.*/
    struct Value {
        union Data {
            int ival;
            double fval;
            bool bval;
        } data;
        ValueType type;
    };

}


#endif //INTERPRETER_VALUE_H
