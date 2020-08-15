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
        for (unsigned i = 0; i < parameters.size(); i++) {
            globalContext.declareVar(parameter_ids[i], parameters[i]);
        }
        for (const auto &stmt:statements)
            stmt->execute(); //TODO check for return value

        globalContext.popScope();

        return Value();//No return statements, return None
    }


}