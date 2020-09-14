//
// Created by gvisan on 06.09.2020.
//

#include "FuncDeclarationStmt.h"

namespace AST {
    FuncDeclarationStmt::FuncDeclarationStmt(yy::location loc, VM::Symbol symbol,
                                             std::vector<VM::Symbol> params,
                                             std::unique_ptr<CompoundStmt> function_body) :
            StmtNode(loc),
            function_symbol(std::move(symbol)),
            parameter_symbols(std::move(params)),
            body(std::move(function_body)) {


    }

    void FuncDeclarationStmt::solveDeclarations(VM::DeclarationStack &stack, std::vector<Error> &errors) {
        if (stack.variableInCurrentScope(function_symbol)) {
            errors.emplace_back("semantic error, duplicate declaration of variable " + function_symbol.symbol_name,
                                location);
        }
        stack.addVariable(function_symbol);

        stack.pushStackFrame();
        for (const auto &symbol:parameter_symbols) {
            if (stack.variableInCurrentScope(symbol)) {
                errors.emplace_back("semantic error, duplicate declaration of the parameter " + symbol.symbol_name,
                                    location);
            }
            stack.addVariable(symbol);
        }
        auto&stmts=body->getStatements();
        for (const auto &statement:stmts) {
            statement->solveDeclarations(stack, errors);
        }
        stack.popStackFrame();
    }

    void FuncDeclarationStmt::emitBytecode(VM::VirtualMachine &vm, VM::BytecodeChunk &chunk) const {
        VM::BytecodeChunk function_chunk;
        auto&stmts=body->getStatements();
        for (const auto &statement:stmts) {
            statement->emitBytecode(vm, function_chunk);
        }
        function_chunk.pushOpcode(VM::Opcode::LOAD_LITERAL);
        function_chunk.pushUInt(0);//load null value

        function_chunk.pushOpcode(VM::Opcode::RETURN_VALUE);

        VM::DefinedFunctionObj *func = GC::globalGc.makeDefinedFunctionObj(function_symbol.symbol_name,
                                                                           parameter_symbols.size(), function_chunk);
        unsigned index = vm.getLiteralCount();
        vm.pushLiteral(VM::makeDefinedFunctionObjValue(func));
        chunk.pushOpcode(VM::Opcode::LOAD_LITERAL);
        chunk.pushUInt(index);
    }

    void FuncDeclarationStmt::checkControlFlow(VM::FlowState &state, std::vector<Error> &errors) const {
        bool in_function=state.isInFunction();
        state.enterFunction();
        auto&stmts=body->getStatements();
        for (const auto &stmt:stmts) {
            stmt->checkControlFlow(state, errors);
        }
        if(!in_function)
            state.exitFunction();
    }

}