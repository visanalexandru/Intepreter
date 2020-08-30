//
// Created by gvisan on 15.08.2020.
//

#include "FuncDeclarationStmt.h"

namespace AST {
    FuncDeclarationStmt::FuncDeclarationStmt(yy::location loc, Symbol sym, std::vector<Symbol> p_syms,
                                             std::vector<std::unique_ptr<StmtNode>> stmts) :
            StmtNode(loc),
            symbol(std::move(sym)),
            parameter_symbols(std::move(p_syms)){

        function=std::make_unique<AST::DefinedFunction>(symbol.symbol_name, parameter_symbols.size(),std::move(stmts));
    }

    void FuncDeclarationStmt::execute() {
        globalContext.declareFunc(symbol, std::move(function));
    }

    void FuncDeclarationStmt::checkControlFlow(FlowState &state,std::vector<Error>&errors) const {
        state.enterFunction();
        for (const auto &stmt:function->getStatements())
            stmt->checkControlFlow(state,errors);
        state.exitFunction();
    }

    void FuncDeclarationStmt::solveDeclarations(AST::DeclarationStack &stack, std::vector<Error> &errors) {
        if(stack.functionExists(symbol))
            errors.emplace_back("semantic error, duplicate declaration of function "+symbol.symbol_name,location);
        else stack.addFunction(symbol);

        /*Solve variable references in the function*/
        stack.pushStackFrame();
        for(const Symbol&sym:parameter_symbols){
            if(stack.variableInCurrentScope(sym))
                errors.emplace_back("semantic error, duplicate declaration of the parameter "+sym.symbol_name,location);
            stack.addVariable(sym);
        }

        for(const auto&stmt:function->getStatements())
            stmt->solveDeclarations(stack,errors);
        stack.popStackFrame();
    }

    void FuncDeclarationStmt::emitBytecode(VM::VirtualMachine &vm) const {

    }


}