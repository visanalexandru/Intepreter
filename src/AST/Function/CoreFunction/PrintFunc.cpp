//
// Created by gvisan on 14.08.2020.
//

#include "PrintFunc.h"


namespace AST {

    PrintFunc::PrintFunc() : Function("print", 1) {


    }

    Value PrintFunc::execute(const std::vector<Value> &parameters) const {
        std::cout << parameters[0].toString()<<std::endl;
        return Value();//None
    }


}