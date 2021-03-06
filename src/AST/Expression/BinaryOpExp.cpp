//
// Created by gvisan on 12.08.2020.
//

#include "BinaryOpExp.h"

namespace AST {
    BinaryOpExp::BinaryOpExp(yy::location loc,AST::BinaryOperator t, std::unique_ptr<ExpNode> l, std::unique_ptr<ExpNode> r) :
            ExpNode(loc),
            type(t),
            left(std::move(l)),
            right(std::move(r)) {
    }

    Value BinaryOpExp::evaluate() const {
        switch (type) {
            case BinaryOperator::Add:
                return left->evaluate() + right->evaluate();
            case BinaryOperator::Subtract:
                return left->evaluate() - right->evaluate();
            case BinaryOperator::Multiply:
                return left->evaluate() * right->evaluate();
            case BinaryOperator::Divide:
                return left->evaluate() / right->evaluate();
            case BinaryOperator ::Equal:
                return left->evaluate()==right->evaluate();
            case BinaryOperator ::Greater:
                return left->evaluate()>right->evaluate();
            case BinaryOperator::GreaterEq:
                return left->evaluate()>=right->evaluate();
            case BinaryOperator ::Less:
                return left->evaluate()<right->evaluate();
            case BinaryOperator ::LessEq:
                return left->evaluate()<=right->evaluate();
            case BinaryOperator ::And:
                return Value(left->evaluate().toBoolObj().asBool() && right->evaluate().toBoolObj().asBool());
            case BinaryOperator ::Or:
                return Value(left->evaluate().toBoolObj().asBool() || right->evaluate().toBoolObj().asBool());
            case BinaryOperator ::NEqual:
                return left->evaluate()!=right->evaluate();
            case BinaryOperator::Modulus:
                return left->evaluate()%right->evaluate();
        }
    }

    void BinaryOpExp::solveVarReferences(AST::DeclarationStack &stack, std::vector<Error> &errors) {
        left->solveVarReferences(stack,errors);
        right->solveVarReferences(stack,errors);
    }
}