//
// Created by gvisan on 10.08.2020.
//

#ifndef INTERPRETER_VALUE_H
#define INTERPRETER_VALUE_H

#include<string>
#include<stdexcept>
#include"Type.h"

namespace AST {
    /*This class represents a value in the interpreted program.*/
    class Value {

    public:

        /*Creates a value with type Int*/
        Value(int value);

        /*Creates a value with type Float*/
        Value(float value);

        /*Creates a value with type String. Strings are immutable, so it creates a copy of the parameter*/
        Value(const std::string &value);

        /*Creates a value with type None*/
        Value();

        /*Deletes the allocated string if it's type is String*/
        ~Value();

        /*Operators:Return the value corresponding to the result of the operation.
         * Throw runtime exceptions if the types are not compatible*/
        Value operator+(const Value &other) const;

        Value operator-(const Value &other) const;

        Value operator*(const Value &other) const;

        Value operator/(const Value &other) const;

        /*Converts the value it is holding to a string*/
        std::string toString() const;


    private:

        /*Union that holds PODs*/
        union Data {
            int ival;
            float fval;
            bool bval;
            std::string *sval;
        };
        Data data;

        const Type type;
    };

}


#endif //INTERPRETER_VALUE_H
