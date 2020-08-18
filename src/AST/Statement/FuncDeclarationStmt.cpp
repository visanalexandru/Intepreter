//
// Created by gvisan on 15.08.2020.
//

#include "FuncDeclarationStmt.h"

namespace AST {
    FuncDeclarationStmt::FuncDeclarationStmt(std::string id, std::vector<std::string> parameter_ids,
                                             std::vector<std::unique_ptr<StmtNode>> stmts) :
            name(std::move(id)),
            identifiers(std::move(parameter_ids)),
            statements(std::move(stmts)) {


    }

    void FuncDeclarationStmt::execute() {
        globalContext.defineFunc(name, std::make_unique<AST::DefinedFunction>(name, std::move(identifiers),
                                                                              std::move(statements)));
    }

    void FuncDeclarationStmt::checkControlFlow(AST::FlowState &state) const {
        state.enterFunction();
        for(const auto&stmt:statements)
            stmt->checkControlFlow(state);
        state.exitFunction();
    }


}