//
// Created by gvisan on 15.08.2020.
//

#ifndef INTERPRETER_FUNCDECLARATIONSTMT_H
#define INTERPRETER_FUNCDECLARATIONSTMT_H

#include"StmtNode.h"
#include"AST/Function/DefinedFunction.h"

namespace AST {
    /*This class is responsible for a function declaration. execute() will construct a function and add
     *to the global context*/
    class FuncDeclarationStmt : public StmtNode {
    private:
        /*These lists will be invalidated after the execute() call because they will be passed as rvalues to the function obj*/
        std::vector<std::string> identifiers;

        std::vector<std::unique_ptr<StmtNode>> statements;

        std::string name;
    public:
        FuncDeclarationStmt(yy::location loc,std::string id, std::vector<std::string> parameter_ids,
                            std::vector<std::unique_ptr<StmtNode>> stmts);

        void execute() override;

        void checkControlFlow(FlowState&state,std::vector<Error>&errors) const override ;
    };

}

#endif //INTERPRETER_FUNCDECLARATIONSTMT_H
