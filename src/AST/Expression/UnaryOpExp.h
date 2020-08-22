//
// Created by gvisan on 12.08.2020.
//

#ifndef INTERPRETER_UNARYOPEXP_H
#define INTERPRETER_UNARYOPEXP_H

#include "Operator.h"
#include "ExpNode.h"

namespace AST {

    class UnaryOpExp : public ExpNode {
    private:
        /*The unary operator type*/
        UnaryOperator type;

        /*The operand to the unary operator*/
        std::unique_ptr<ExpNode> exp;

    public:
        UnaryOpExp(yy::location loc,UnaryOperator t, std::unique_ptr<ExpNode> op);

        Value evaluate() const override;
    };
}


#endif //INTERPRETER_UNARYOPEXP_H
