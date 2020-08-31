//
// Created by gvisan on 12.08.2020.
//

#ifndef INTERPRETER_BINARYOPEXP_H
#define INTERPRETER_BINARYOPEXP_H

#include "Operator.h"
#include "ExpNode.h"

namespace AST {

    class BinaryOpExp : public ExpNode {
    private:
        /*The binary operator type*/
        BinaryOperator type;

        /*The expression on the left side of the operator*/
        std::unique_ptr<ExpNode> left;

        /*The expression on the right side of the operator*/
        std::unique_ptr<ExpNode> right;

    public:
        BinaryOpExp(yy::location loc, BinaryOperator t, std::unique_ptr<ExpNode> l, std::unique_ptr<ExpNode> r);

        Value evaluate() const override;

        void solveVarReferences(AST::DeclarationStack &stack, std::vector<Error> &errors) override;

        void emitBytecode(VM::VirtualMachine&vm,VM::BytecodeChunk&chunk) const override;
    };
}


#endif //INTERPRETER_BINARYOPEXP_H
