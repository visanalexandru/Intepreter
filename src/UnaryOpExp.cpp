//
// Created by gvisan on 12.08.2020.
//

#include "UnaryOpExp.h"

namespace AST {
    UnaryOpExp::UnaryOpExp(AST::UnaryOperator t, std::unique_ptr<ExpNode> op) :
            type(t),
            exp(std::move(op)) {
    }


    Value UnaryOpExp::evaluate() const {
        switch (type) {
            case UnaryOperator::Minus:
                return -exp->evaluate();
        }
    }

}