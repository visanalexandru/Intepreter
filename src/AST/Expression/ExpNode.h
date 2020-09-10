//
// Created by gvisan on 12.08.2020.
//

#ifndef INTERPRETER_EXPNODE_H
#define INTERPRETER_EXPNODE_H

#include<vector>
#include<memory>
#include <location.hh>
#include"VM/Preprocess/DeclarationStack.h"
#include "VM/VirtualMachine.h"
#include "Error.h"
namespace AST {
    /*This class represents an expression in the AST.*/
    class ExpNode {
    protected:
        /*The location of the expression.*/
        yy::location location;
    public:
        explicit ExpNode(yy::location loc);

        virtual ~ExpNode() = default;

        /*Solves declarations, converts symbols to the location in the stack where the variable will be*/
        virtual void solveVarReferences(VM::DeclarationStack&stack,std::vector<Error>&errors)=0 ;

        /*Converts the expression syntax tree into bytecode*/
        virtual void emitBytecode(VM::VirtualMachine&vm,VM::BytecodeChunk&chunk) const =0;
    };
}

#endif //INTERPRETER_EXPNODE_H
