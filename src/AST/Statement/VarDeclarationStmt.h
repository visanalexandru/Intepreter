//
// Created by gvisan on 14.08.2020.
//

#ifndef INTERPRETER_VARDECLARATIONSTMT_H
#define INTERPRETER_VARDECLARATIONSTMT_H

#include "StmtNode.h"
#include "AST/Context.h"
#include "AST/Expression/ExpNode.h"
#include "AST/Symbol.h"

namespace AST {
    /*This class is responsible for the declaration of a variable at runtime*/
    class VarDeclarationStmt : public StmtNode {
    private:
        const Symbol symbol;

        /*The expression on the right side of the declaration*/
        std::shared_ptr<ExpNode> value;
    public:
        /*Declares the variable, using the global context object*/
        void execute() override;

        /*Declares the variable with value None*/
        VarDeclarationStmt(yy::location loc, Symbol sym);

        /*Declares the variable with the value of the expression*/
        VarDeclarationStmt(yy::location loc, Symbol sym, std::shared_ptr<ExpNode> exp);

        void checkControlFlow(FlowState &state,
                              std::vector<Error> &errors) const override {};//no control flow errors can happen here

        void checkDeclarations(DeclarationStack&stack,std::vector<Error>&errors) const override ;
    };
}


#endif //INTERPRETER_VARDECLARATIONSTMT_H
