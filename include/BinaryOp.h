//
// Created by gvisan on 12.08.2020.
//

#ifndef INTERPRETER_BINARYOP_H
#define INTERPRETER_BINARYOP_H

#include "Operator.h"
#include "ExpNode.h"

namespace AST {

    class BinaryOp : public ExpNode {
    private:
        /*The binary operator type*/
        BinaryOperator type;

        /*The expression on the left side of the operator*/
        std::unique_ptr<ExpNode> left;

        /*The expression on the right side of the operator*/
        std::unique_ptr<ExpNode> right;

    public:
        BinaryOp(BinaryOperator t, std::unique_ptr<ExpNode> l, std::unique_ptr<ExpNode> r);

        Value evaluate() const override;
    };
}


#endif //INTERPRETER_BINARYOP_H
