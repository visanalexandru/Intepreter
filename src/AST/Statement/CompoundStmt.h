//
// Created by gvisan on 28.08.2020.
//

#ifndef INTERPRETER_COMPOUNDSTMT_H
#define INTERPRETER_COMPOUNDSTMT_H
#include"StmtNode.h"

namespace AST{


    class CompoundStmt: public StmtNode {
    private:
        std::vector<std::unique_ptr<StmtNode>> statements;

        unsigned to_pop;/*The number of declarations in the block scope*/

    public:
        CompoundStmt(yy::location loc, std::vector<std::unique_ptr<StmtNode>> stmts);

        void checkControlFlow(VM::FlowState&state,std::vector<Error>&errors) const override;

        void solveDeclarations(VM::DeclarationStack&stack,std::vector<Error>&errors) override;

        void emitBytecode(VM::VirtualMachine&vm,VM::BytecodeChunk&chunk) const override;

    };


}


#endif //INTERPRETER_COMPOUNDSTMT_H
