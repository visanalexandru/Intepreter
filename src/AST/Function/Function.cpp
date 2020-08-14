//
// Created by gvisan on 14.08.2020.
//

#include "Function.h"

namespace AST {
    Function::Function(std::string identifier, int num_params) :
            name(std::move(identifier)),
            arity(num_params) {

    }

    Value Function::run(const std::vector<Value> &parameters) const {
        if (parameters.size() != arity) {
            throw std::runtime_error(name + "() needs " + std::to_string(arity) + " parameters but " +
                                     std::to_string(parameters.size()) + " were provided");
        }
        return execute(parameters);
    }

    std::string Function::getName() {
        return name;
    }


}