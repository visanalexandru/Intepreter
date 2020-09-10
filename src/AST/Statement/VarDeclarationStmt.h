//
// Created by gvisan on 14.08.2020.
//

#ifndef INTERPRETER_VARDECLARATIONSTMT_H
#define INTERPRETER_VARDECLARATIONSTMT_H

#include "StmtNode.h"
#include "AST/Expression/ExpNode.h"
#include "VM/SymbolTable/Symbol.h"
#include "VM/Value/Arithmetic.h"
namespace AST {
    /*This class represents a variable declaration*/
    class VarDeclarationStmt : public StmtNode {
    private:
        const VM::Symbol symbol;

        /*The expression on the right side of the declaration*/
        std::shared_ptr<ExpNode> value;
    public:
        /*Declares the variable with value None*/
        VarDeclarationStmt(yy::location loc, VM::Symbol sym);

        /*Declares the variable with the value of the expression*/
        VarDeclarationStmt(yy::location loc, VM::Symbol sym, std::shared_ptr<ExpNode> exp);

        void checkControlFlow(VM::FlowState &state,
                              std::vector<Error> &errors) const override {};//no control flow errors can happen here

        void emitBytecode(VM::VirtualMachine&vm,VM::BytecodeChunk&chunk) const override;

        void solveDeclarations(VM::DeclarationStack&stack,std::vector<Error>&errors) override ;
    };
}


#endif //INTERPRETER_VARDECLARATIONSTMT_H
