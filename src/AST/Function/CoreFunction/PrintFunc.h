//
// Created by gvisan on 14.08.2020.
//

#ifndef INTERPRETER_PRINTFUNC_H
#define INTERPRETER_PRINTFUNC_H

#include<iostream>
#include"AST/Function/Function.h"


namespace AST {
    /*Print function,prints the single value that is passed to the execute() function*/
    /*Return value:None*/
    class PrintFunc : public Function {
    public:
        Value execute(const std::vector<Value> &parameters) const override;

        PrintFunc();
    };
}


#endif //INTERPRETER_PRINTFUNC_H
