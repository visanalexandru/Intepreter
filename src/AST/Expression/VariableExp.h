//
// Created by gvisan on 14.08.2020.
//

#ifndef INTERPRETER_VARIABLEEXP_H
#define INTERPRETER_VARIABLEEXP_H

#include "ExpNode.h"
#include "AST/Context.h"

namespace AST {
    /*This class represents a variable read in the interpreted program*/
    class VariableExp : public ExpNode {
    private:
        const std::string name;
    public:
        VariableExp(std::string varname);

        /*Returns the value of the variable that has that name*/
        Value evaluate() const override;
    };
}


#endif //INTERPRETER_VARIABLEEXP_H
