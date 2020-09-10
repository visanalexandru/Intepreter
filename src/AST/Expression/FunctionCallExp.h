//
// Created by gvisan on 04.09.2020.
//

#ifndef INTERPRETER_FUNCTIONCALLEXP_H
#define INTERPRETER_FUNCTIONCALLEXP_H

#include "ExpNode.h"

namespace AST {
    /*This class represents a function call in the interpreted program*/
    class FunctionCallExp : public ExpNode {
    private:
        /*Arguments to the function call*/
        std::vector<std::unique_ptr<ExpNode>> arguments;

        /*The callable expression*/
        std::unique_ptr<ExpNode> expression;
    public:
        FunctionCallExp(yy::location location, std::unique_ptr<ExpNode> exp,
                        std::vector<std::unique_ptr<ExpNode>> params);

        /*Recursively solve references for the expression that must be called and the parameters*/
        void solveVarReferences(VM::DeclarationStack &stack, std::vector<Error> &errors) override;

        void emitBytecode(VM::VirtualMachine &vm, VM::BytecodeChunk &chunk) const override;
    };
}


#endif //INTERPRETER_FUNCTIONCALLEXP_H
