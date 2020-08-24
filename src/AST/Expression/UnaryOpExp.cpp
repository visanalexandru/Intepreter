//
// Created by gvisan on 12.08.2020.
//

#include "UnaryOpExp.h"

namespace AST {
    UnaryOpExp::UnaryOpExp(yy::location loc,AST::UnaryOperator t, std::unique_ptr<ExpNode> op) :
            ExpNode(loc),
            type(t),
            exp(std::move(op)) {
    }


    Value UnaryOpExp::evaluate() const {
        switch (type) {
            case UnaryOperator::Minus:
                return -exp->evaluate();
            case UnaryOperator ::Not:
                return Value(!(exp->evaluate().toBoolObj().asBool()));
        }
    }

    void UnaryOpExp::solveVarReferences(AST::DeclarationStack &stack, std::vector<Error> &errors) {
        exp->solveVarReferences(stack,errors);
    }

}