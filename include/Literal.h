//
// Created by gvisan on 12.08.2020.
//

#ifndef INTERPRETER_LITERAL_H
#define INTERPRETER_LITERAL_H

#include "ExpNode.h"
#include "Value.h"

namespace AST {
    /*This class represents a literal value, a terminal node in the AST*/
    class Literal : public ExpNode {
    private:
        Value value;
    public:
        Literal(Value val);

        /*Just returns the value*/
        Value evaluate() const override;
    };

}


#endif //INTERPRETER_LITERAL_H
