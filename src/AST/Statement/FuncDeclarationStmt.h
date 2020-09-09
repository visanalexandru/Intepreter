//
// Created by gvisan on 06.09.2020.
//

#ifndef INTERPRETER_FUNCDECLARATIONSTMT_H
#define INTERPRETER_FUNCDECLARATIONSTMT_H

#include "StmtNode.h"
#include "GC/GarbageCollector.h"
namespace AST {
    class FuncDeclarationStmt : public StmtNode {
    private:
        std::vector<std::unique_ptr<StmtNode>> to_execute;

        VM::Symbol function_symbol;

        std::vector<VM::Symbol> parameter_symbols;



    public:
        FuncDeclarationStmt(yy::location loc,VM::Symbol symbol,std::vector<VM::Symbol> params,std::vector<std::unique_ptr<StmtNode>> stmts);

        void solveDeclarations(VM::DeclarationStack&stack,std::vector<Error>&errors) override;

        void emitBytecode(VM::VirtualMachine&vm,VM::BytecodeChunk&chunk) const override;

        void checkControlFlow(VM::FlowState &state, std::vector<Error> &errors) const override;
    };
}


#endif //INTERPRETER_FUNCDECLARATIONSTMT_H
