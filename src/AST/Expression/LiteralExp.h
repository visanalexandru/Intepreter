//
// Created by gvisan on 12.08.2020.
//

#ifndef INTERPRETER_LITERALEXP_H
#define INTERPRETER_LITERALEXP_H

#include "ExpNode.h"
#include "AST/Value/Value.h"

namespace AST {
    /*This class represents a literal value, a terminal node in the AST*/
    class LiteralExp : public ExpNode {
    private:
        Value value;
    public:
        explicit LiteralExp(Value val);

        /*Just returns the value*/
        Value evaluate() const override;
    };

}


#endif //INTERPRETER_LITERALEXP_H
