//
// Created by gvisan on 14.08.2020.
//

#ifndef INTERPRETER_VARIABLEEXP_H
#define INTERPRETER_VARIABLEEXP_H

#include "ExpNode.h"
#include "VM/SymbolTable/Symbol.h"
#include "Error.h"

namespace AST {
    /*This class represents a variable dereference in the interpreted program.
     * It could be an assignment or a read*/
    class VariableExp : public ExpNode {
    private:
        /*The symbol of the variable that needs to be read*/
        const VM::Symbol symbol;

        VM::VariableLocation var_location;

        std::unique_ptr<ExpNode> assign;
    public:
        VariableExp(yy::location loc,VM::Symbol sym);

        VariableExp(yy::location loc,VM::Symbol sym,std::unique_ptr<ExpNode> to_assign);

        /*Convert the variable symbol to a VariableLocation, that holds information about the
         * location in the stack of the var. If the assign expression is not null, resolve variables
         * for it too.*/
        void solveVarReferences(VM::DeclarationStack &stack, std::vector<Error> &errors) override;

        void emitBytecode(VM::VirtualMachine&vm,VM::BytecodeChunk&chunk) const override;
    };
}


#endif //INTERPRETER_VARIABLEEXP_H
