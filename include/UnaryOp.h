//
// Created by gvisan on 12.08.2020.
//

#ifndef INTERPRETER_UNARYOP_H
#define INTERPRETER_UNARYOP_H

#include "Operator.h"
#include "ExpNode.h"

namespace AST {

    class UnaryOp : public ExpNode {
    private:
        /*The unary operator type*/
        UnaryOperator type;

        /*The operand to the unary operator*/
        std::unique_ptr<ExpNode> exp;

    public:
        UnaryOp(UnaryOperator t, std::unique_ptr<ExpNode> op);

        Value evaluate() const override;
    };
}


#endif //INTERPRETER_UNARYOP_H
