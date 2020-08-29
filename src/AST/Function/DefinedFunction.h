//
// Created by gvisan on 15.08.2020.
//

#ifndef INTERPRETER_DEFINEDFUNCTION_H
#define INTERPRETER_DEFINEDFUNCTION_H

#include<memory>
#include "Function.h"
#include "AST/Context.h"
#include"AST/Statement/StmtNode.h"
#include "AST/Symbol.h"
namespace AST {
    /*This class represents a user-defined function. We should create this class when we reach a function declaration
     * in the interpreted program.
     * Whenever this function is called by run(), we create a new scope in the global context, declare each parameter
     * in the current scope by its parameter id (given by its order) with the values provided.*/
    class DefinedFunction : public Function {
    private:
        /*Statements to execute in order. If one statement has returned a value, stop executing and return its return value.*/
        const std::vector<std::unique_ptr<StmtNode>> statements;

    public:
        const std::vector<std::unique_ptr<StmtNode>>&getStatements() const;

        DefinedFunction(std::string identifier,unsigned long arity,
                        std::vector<std::unique_ptr<StmtNode>> to_execute);

        Value execute(const std::vector<Value> &parameters) const override;

    };
}


#endif //INTERPRETER_DEFINEDFUNCTION_H
