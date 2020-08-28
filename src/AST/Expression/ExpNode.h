//
// Created by gvisan on 12.08.2020.
//

#ifndef INTERPRETER_EXPNODE_H
#define INTERPRETER_EXPNODE_H

#include<vector>
#include<memory>
#include <location.hh>
#include"AST/Value/Value.h"
#include"AST/Preprocess/DeclarationStack.h"
#include "VirtualMachine/VirtualMachine.h"
#include "Error.h"
namespace AST {
    /*This class represents an expression node in the AST. Binary, unary, assigment operators etc. derive from this class.*/
    /*The classes that derive from this class must implement the evaluate() function.*/

    class ExpNode {
    protected:
        /*The location of the expression.*/
        yy::location location;
    public:
        explicit ExpNode(yy::location loc);
        /*Evaluates the expression based on the child nodes*/
        virtual Value evaluate() const = 0;

        /*Default virtual constructor*/
        virtual ~ExpNode() = default;

        virtual void solveVarReferences(DeclarationStack&stack,std::vector<Error>&errors)=0 ;

        virtual void emitBytecode(VM::VirtualMachine&vm) const =0;
    };
}

#endif //INTERPRETER_EXPNODE_H
