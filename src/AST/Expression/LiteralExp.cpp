//
// Created by gvisan on 12.08.2020.
//

#include "LiteralExp.h"

namespace AST {

    LiteralExp::LiteralExp(yy::location loc,AST::Value val) : ExpNode(loc),value(std::move(val)) {

    }

    Value LiteralExp::evaluate() const {
        return value;
    }
}