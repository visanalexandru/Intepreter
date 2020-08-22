//
// Created by gvisan on 15.08.2020.
//

#ifndef INTERPRETER_FUNCDECLARATIONSTMT_H
#define INTERPRETER_FUNCDECLARATIONSTMT_H

#include"StmtNode.h"
#include"AST/Function/DefinedFunction.h"
#include "AST/Symbol.h"
namespace AST {
    /*This class is responsible for a function declaration. execute() will construct a function and add
     *to the global context*/
    class FuncDeclarationStmt : public StmtNode {
    private:
        /*These lists will be invalidated after the execute() call because they will be passed as rvalues to the function obj*/
        std::vector<Symbol> parameter_symbols;

        std::vector<std::unique_ptr<StmtNode>> statements;

        /*The symbol of the function*/
        const Symbol symbol;
    public:
        FuncDeclarationStmt(yy::location loc,Symbol sym, std::vector<Symbol> p_syms,
                            std::vector<std::unique_ptr<StmtNode>> stmts);

        void execute() override;

        void checkControlFlow(FlowState&state,std::vector<Error>&errors) const override ;

        void checkDeclarations(DeclarationStack&stack,std::vector<Error>&errors) const override ;
    };

}

#endif //INTERPRETER_FUNCDECLARATIONSTMT_H
