//
// Created by gvisan on 15.08.2020.
//

#include "DefinedFunction.h"

namespace AST {
    DefinedFunction::DefinedFunction(std::string identifier, std::vector<std::string> parameters,
                                     std::vector<std::unique_ptr<StmtNode>> to_execute) :
            Function(std::move(identifier), parameters.size()),
            parameter_ids(std::move(parameters)),
            statements(std::move(to_execute)) {


    }

    Value DefinedFunction::execute(const std::vector<Value> &parameters) const {
        globalContext.pushScope();
        for (unsigned long i = 0; i < parameters.size(); i++) {
            globalContext.declareVar(parameter_ids[i], parameters[i]);
        }
        Value to_return;//if no return statements, return None

        for (const auto &stmt:statements) {
            stmt->execute();
            if (stmt->hasReturned()) {//Statement is/contains a return statement
                to_return = stmt->getReturnValue();
                break;
            }
        }
        globalContext.popScope();

        return to_return;
    }


}