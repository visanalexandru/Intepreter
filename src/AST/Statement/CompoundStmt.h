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

    public:
        CompoundStmt(yy::location loc, std::vector<std::unique_ptr<StmtNode>> stmts);

        void execute() override;

        void checkControlFlow(FlowState&state,std::vector<Error>&errors) const override;

        void checkDeclarations(DeclarationStack&stack,std::vector<Error>&errors) const override;

        /*Used to inject statements, like variable declarations in functions.*/
        std::vector<std::unique_ptr<StmtNode>>& getStatements();

    };


}


#endif //INTERPRETER_COMPOUNDSTMT_H
