//
// Created by gvisan on 28.08.2020.
//

#ifndef INTERPRETER_COMPOUNDSTMT_H
#define INTERPRETER_COMPOUNDSTMT_H
#include"StmtNode.h"

namespace AST{

    /*This class represents a compound statement in the interpreted program. It is
     * just a list of statements that execute in a new scope*/
    class CompoundStmt: public StmtNode {
    private:
        std::vector<std::unique_ptr<StmtNode>> statements;

        unsigned to_pop;/*The number of declarations in the block scope*/

    public:
        /*Create a compound statement using a list of statements*/
        CompoundStmt(yy::location loc, std::vector<std::unique_ptr<StmtNode>> stmts);

        /*Create a compound statement using just a statement. Useful for having non-compound
         * statements in while/if etc statements.*/
        CompoundStmt(yy::location loc, std::unique_ptr<StmtNode> stmt);

        void checkControlFlow(VM::FlowState&state,std::vector<Error>&errors) const override;

        /*Push a new scope in the declaration stack and then solve declarations for all the statements
         * in it's body*/
        void solveDeclarations(VM::DeclarationStack&stack,std::vector<Error>&errors) override;

        void emitBytecode(VM::VirtualMachine&vm,VM::BytecodeChunk&chunk) const override;

        /*Return a reference to the list of statements*/
        const std::vector<std::unique_ptr<StmtNode>>& getStatements() const;

    };


}


#endif //INTERPRETER_COMPOUNDSTMT_H
