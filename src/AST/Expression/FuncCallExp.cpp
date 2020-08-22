//
// Created by gvisan on 14.08.2020.
//

#include "FuncCallExp.h"

namespace AST {

    FuncCallExp::FuncCallExp(yy::location loc,Symbol sym, std::vector<std::unique_ptr<ExpNode>> params) :
            ExpNode(loc),
            symbol(std::move(sym)),
            parameters(std::move(params)) {


    }

    Value FuncCallExp::evaluate() const {
        if(!globalContext.isFuncDeclared(symbol.symbol_id))
            throw std::runtime_error(Error("runtime error, function has not been declared: " + symbol.symbol_name,location).toString());
        std::vector<Value> values;
        for (const auto &expression:parameters) {
            values.push_back(expression->evaluate());
        }
        return globalContext.getFunc(symbol.symbol_id)->run(values);
    }

}
