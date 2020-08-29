//
// Created by gvisan on 28.08.2020.
//

#ifndef INTERPRETER_COMPOUNDSTMT_H
#define INTERPRETER_COMPOUNDSTMT_H
#include"StmtNode.h"
#include"AST/Context.h"

namespace AST{


    class CompoundStmt: public StmtNode {
    private:
        std::vector<std::unique_ptr<StmtNode>> statements;

        unsigned long to_pop;/*The number of declarations in the block scope*/

    public:
        CompoundStmt(yy::location loc, std::vector<std::unique_ptr<StmtNode>> stmts);

        void execute() override;

        void checkControlFlow(FlowState&state,std::vector<Error>&errors) const override;

        void solveDeclarations(DeclarationStack&stack,std::vector<Error>&errors) override;

        /*Used to inject statements, like variable declarations in functions.*/
        std::vector<std::unique_ptr<StmtNode>>& getStatements();

    };


}


#endif //INTERPRETER_COMPOUNDSTMT_H
