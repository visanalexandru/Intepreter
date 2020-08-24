//
// Created by gvisan on 15.08.2020.
//

#include "DefinedFunction.h"

namespace AST {
    DefinedFunction::DefinedFunction(std::string identifier, std::vector<Symbol> p_symbols,
                                     std::vector<std::unique_ptr<StmtNode>> to_execute) :
            Function(std::move(identifier), p_symbols.size()),
            parameter_symbols(std::move(p_symbols)),
            statements(std::move(to_execute)) {


    }

    Value DefinedFunction::execute(const std::vector<Value> &parameters) const {
        globalContext.pushScope();
        for(const Value&param:parameters){
            globalContext.pushVar(param);
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