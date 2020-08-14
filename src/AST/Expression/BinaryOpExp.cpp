//
// Created by gvisan on 12.08.2020.
//

#include "BinaryOpExp.h"

namespace AST {
    BinaryOpExp::BinaryOpExp(AST::BinaryOperator t, std::unique_ptr<ExpNode> l, std::unique_ptr<ExpNode> r) :
            type(t),
            left(std::move(l)),
            right(std::move(r)) {
    }

    Value BinaryOpExp::evaluate() const {
        switch (type) {
            case BinaryOperator::Addition:
                return left->evaluate() + right->evaluate();
            case BinaryOperator::Subtraction:
                return left->evaluate() - right->evaluate();
            case BinaryOperator::Multiplication:
                return left->evaluate() * right->evaluate();
            case BinaryOperator::Division:
                return left->evaluate() / right->evaluate();
        }
    }
}