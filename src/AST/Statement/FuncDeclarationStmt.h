//
// Created by gvisan on 06.09.2020.
//

#ifndef INTERPRETER_FUNCDECLARATIONSTMT_H
#define INTERPRETER_FUNCDECLARATIONSTMT_H

#include "StmtNode.h"
#include "GC/GarbageCollector.h"
#include "CompoundStmt.h"
namespace AST {
    /*This class represents a function declaration in the interpreted program*/
    class FuncDeclarationStmt : public StmtNode {
    private:
        /*The function body*/
        std::unique_ptr<CompoundStmt> body;
        /*The function symbols*/
        VM::Symbol function_symbol;

        /*The list of parameter symbols*/
        std::vector<VM::Symbol> parameter_symbols;


    public:
        FuncDeclarationStmt(yy::location loc,VM::Symbol symbol,std::vector<VM::Symbol> params,std::unique_ptr<CompoundStmt> body);

        /*Push a new stack frame to the declaration stack,push the parameter symbols into the declaration stack */
        void solveDeclarations(VM::DeclarationStack&stack,std::vector<Error>&errors) override;

        void emitBytecode(VM::VirtualMachine&vm,VM::BytecodeChunk&chunk) const override;

        /*Check for return statements outside functions*/
        void checkControlFlow(VM::FlowState &state, std::vector<Error> &errors) const override;
    };
}


#endif //INTERPRETER_FUNCDECLARATIONSTMT_H
