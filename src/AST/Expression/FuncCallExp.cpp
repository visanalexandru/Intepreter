//
// Created by gvisan on 14.08.2020.
//

#include "FuncCallExp.h"

namespace AST {

    FuncCallExp::FuncCallExp(std::string id, std::vector<std::unique_ptr<ExpNode>> params) :
            name(std::move(id)),
            parameters(std::move(params)) {


    }

    Value FuncCallExp::evaluate() const {
        std::vector<Value> values;
        for (const auto &expression:parameters) {
            values.push_back(expression->evaluate());
        }
        return globalContext.getFunc(name)->run(values);
    }

}
