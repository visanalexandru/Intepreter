//
// Created by gvisan on 14.08.2020.
//

#ifndef INTERPRETER_FUNCCALLEXP_H
#define INTERPRETER_FUNCCALLEXP_H

#include"ExpNode.h"
#include"AST/Context.h"
#include "AST/Symbol.h"
#include "Error.h"

namespace AST {
    /*This class represents a function call. The evaluate() function will evaluate the parameter expressions,
     *and then run the function that has that name with the corresponding values*/
    class FuncCallExp : public ExpNode {
    private:
        /*The symbol of the function that needs to be called*/
        const Symbol symbol;
        /*These must be evaluated */
        const std::vector<std::unique_ptr<ExpNode>> parameters;
    public:
        FuncCallExp(yy::location loc,Symbol sym, std::vector<std::unique_ptr<ExpNode>> params);

        /*Throw runtime error if the function was not declared*/
        Value evaluate() const override;

        void solveVarReferences(AST::DeclarationStack &stack, std::vector<Error> &errors) override;

        void emitBytecode(VM::VirtualMachine&vm,VM::BytecodeChunk&chunk) const override;
    };

}


#endif //INTERPRETER_FUNCCALLEXP_H
