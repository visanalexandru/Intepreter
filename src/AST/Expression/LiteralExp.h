//
// Created by gvisan on 12.08.2020.
//

#ifndef INTERPRETER_LITERALEXP_H
#define INTERPRETER_LITERALEXP_H

#include "ExpNode.h"
#include "VM/Value/Value.h"
#include "VM/VirtualMachine.h"
namespace AST {
    /*This class represents a literal value, a terminal node in the AST*/
    class LiteralExp : public ExpNode {
    private:
        VM::Value value;
    public:
        LiteralExp(yy::location loc,VM::Value val);

        void solveVarReferences(AST::DeclarationStack &stack, std::vector<Error> &errors) override {};

        void emitBytecode(VM::VirtualMachine&vm,VM::BytecodeChunk&chunk) const override;
    };

}


#endif //INTERPRETER_LITERALEXP_H
