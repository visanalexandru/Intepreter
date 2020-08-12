//
// Created by gvisan on 12.08.2020.
//

#include "Literal.h"

namespace AST {

    Literal::Literal(AST::Value val) : value(std::move(val)) {

    }

    Value Literal::evaluate() const {
        return value;
    }
}