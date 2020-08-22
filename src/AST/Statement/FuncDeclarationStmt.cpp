//
// Created by gvisan on 15.08.2020.
//

#include "FuncDeclarationStmt.h"

namespace AST {
    FuncDeclarationStmt::FuncDeclarationStmt(yy::location loc, Symbol sym, std::vector<Symbol> p_syms,
                                             std::vector<std::unique_ptr<StmtNode>> stmts) :
            StmtNode(loc),
            symbol(std::move(sym)),
            parameter_symbols(std::move(p_syms)),
            statements(std::move(stmts)) {


    }

    void FuncDeclarationStmt::execute() {
        globalContext.declareFunc(symbol.symbol_id, std::make_unique<AST::DefinedFunction>(symbol.symbol_name, std::move(parameter_symbols),
                                                                              std::move(statements)));
    }

    void FuncDeclarationStmt::checkControlFlow(FlowState &state,std::vector<Error>&errors) const {
        state.enterFunction();
        for (const auto &stmt:statements)
            stmt->checkControlFlow(state,errors);
        state.exitFunction();
    }

    void FuncDeclarationStmt::checkDeclarations(AST::DeclarationStack &stack, std::vector<Error> &errors) const {
        if(stack.functionExists(symbol.symbol_id))
            errors.emplace_back("semantic error, duplicate declaration of function "+symbol.symbol_name,location);
        stack.addFunction(symbol.symbol_id);

        stack.push_scope();
        for(const Symbol&sym:parameter_symbols)
            stack.addVariable(sym.symbol_id);
        for(const auto&stmt:statements)
            stmt->checkDeclarations(stack,errors);
        stack.pop_scope();
    }


}