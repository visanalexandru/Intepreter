//
// Created by gvisan on 14.08.2020.
//

#ifndef INTERPRETER_FUNCTION_H
#define INTERPRETER_FUNCTION_H

#include<vector>
#include "AST/Value/Value.h"

namespace AST {
    /*This class represents a function in the interpreted program. Every class that derives from this class must
     * implement the execute() function*/
    class Function {
    protected:
        /*Function name*/
        const std::string name;

        /*The number of parameters*/
        const int arity;

        /*Execute the function. Consider the size of the list of parameters to be equal to the function arity,
         * it is checked when calling run()*/
        virtual Value execute(const std::vector<Value> &parameters) const = 0;

    public:
        Function(std::string identifier, int num_params);

        virtual ~Function() = default;

        /*Check the correct arity, execute the function and return the return value*/
        Value run(const std::vector<Value> &parameters) const;

        std::string getName();
    };

}


#endif //INTERPRETER_FUNCTION_H
