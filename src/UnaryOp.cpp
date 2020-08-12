//
// Created by gvisan on 12.08.2020.
//

#include "UnaryOp.h"

namespace AST {
    UnaryOp::UnaryOp(AST::UnaryOperator t, std::unique_ptr<ExpNode> op) :
            type(t),
            exp(std::move(op)) {
    }


    Value UnaryOp::evaluate() const {
        switch (type) {
            case UnaryOperator::Minus:
                return -exp->evaluate();
        }
    }

}