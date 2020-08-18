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
        explicit Value(int value);

        /*Creates a value with type Float*/
        explicit Value(double value);

        /*Creates a value with type String. Strings are immutable, so it creates a copy of the parameter*/
        explicit Value(const std::string &value);

        /*Creates a value with type Bool*/
        explicit Value(bool value);

        /*Creates a value with type None*/
        Value();

        /*Deletes the allocated string if it's type is String*/
        ~Value();

        /*Copy constructor. If the other value's type is a string, or another immutable type that requires a pointer ,
         * allocate a new copy*/
        Value(const Value &other);

        /*Move constructor*/
        Value(Value &&other) noexcept;

        /*Copy assignment operator.*/
        Value &operator=(Value other);


        /*Operators:Return the value corresponding to the result of the operation.
         * Throw runtime exceptions if the types are not compatible*/
        Value operator+(const Value &other) const;

        Value operator-(const Value &other) const;

        Value operator*(const Value &other) const;

        Value operator/(const Value &other) const;

        Value operator-() const;

        /*Boolean operators, return bool-type value.*/
        Value operator==(const Value &other) const;

        Value operator!=(const Value&other) const;

        Value operator>(const Value &other) const;

        Value operator<(const Value &other) const;

        Value operator>=(const Value &other) const;

        Value operator<=(const Value &other) const;

        /*Converts the value it is holding to a string*/
        std::string toString() const;

        Type getType() const;

        /*Converts this value object to other value object.Throws exception if conversion is not possible.*/
        Value toIntObj() const;

        Value toFloatObj() const;

        Value toStringObj() const;

        Value toBoolObj() const;

        bool isNumerical() const;

        /*Returns the union's members. Use this functions only if you know the object type!
         *Ex: using asInt() when the obj type is Float is undefined!*/
        int asInt() const;

        double asFloat() const;

        bool asBool() const;

        std::string asString() const;


    private:
        /*Swap values*/
        void swap(Value &other);

        /*Union that holds PODs*/
        union Data {
            int ival;
            double fval;
            bool bval;
            std::string *sval;
        };
        Data data;

        Type type;
    };

}


#endif //INTERPRETER_VALUE_H
