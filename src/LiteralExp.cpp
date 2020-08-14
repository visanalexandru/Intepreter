//
// Created by gvisan on 12.08.2020.
//

#include "LiteralExp.h"

namespace AST {

    LiteralExp::LiteralExp(AST::Value val) : value(std::move(val)) {

    }

    Value LiteralExp::evaluate() const {
        return value;
    }
}