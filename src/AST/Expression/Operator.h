//
// Created by gvisan on 12.08.2020.
//

#ifndef INTERPRETER_OPERATOR_H
#define INTERPRETER_OPERATOR_H

/*Operator enumerators*/
namespace AST {

    enum class BinaryOperator {
        Addition,
        Subtraction,
        Multiplication,
        Division
    };

    enum class UnaryOperator {
        Minus,
    };

}


#endif //INTERPRETER_OPERATOR_H


