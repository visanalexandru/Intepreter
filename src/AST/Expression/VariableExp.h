//
// Created by gvisan on 14.08.2020.
//

#ifndef INTERPRETER_VARIABLEEXP_H
#define INTERPRETER_VARIABLEEXP_H

#include "ExpNode.h"
#include "AST/Context.h"
#include "AST/Symbol.h"
#include "Error.h"

namespace AST {
    /*This class represents a variable dereference in the interpreted program.
     * It could be an assignment or a read*/
    class VariableExp : public ExpNode {
    private:
        /*The symbol of the variable that needs to be read*/
        const Symbol symbol;

        VariableLocation var_location;

        std::unique_ptr<ExpNode> assign;
    public:
        VariableExp(yy::location loc,Symbol sym);

        VariableExp(yy::location loc,Symbol sym,std::unique_ptr<ExpNode> to_assign);

        /*Returns the value of the variable that has that name*/
        Value evaluate() const override;

        void solveVarReferences(AST::DeclarationStack &stack, std::vector<Error> &errors) override;

        void emitBytecode(VM::VirtualMachine&vm,VM::BytecodeChunk&chunk) const override;
    };
}


#endif //INTERPRETER_VARIABLEEXP_H
