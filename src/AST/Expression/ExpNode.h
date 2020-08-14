//
// Created by gvisan on 12.08.2020.
//

#ifndef INTERPRETER_EXPNODE_H
#define INTERPRETER_EXPNODE_H

#include<vector>
#include<memory>
#include"AST/Value/Value.h"

namespace AST {
    /*This class represents an expression node in the AST. Binary, unary, assigment operators etc. derive from this class.*/
    /*The classes that derive from this class must implement the evaluate() function.*/

    class ExpNode {
    public:
        /*Evaluates the expression based on the child nodes*/
        virtual Value evaluate() const = 0;

        /*Default virtual constructor*/
        virtual ~ExpNode() = default;
    };
}

#endif //INTERPRETER_EXPNODE_H
