//
// Created by gvisan on 02.09.2020.
//

#ifndef INTERPRETER_ARITHMETIC_H
#define INTERPRETER_ARITHMETIC_H

#include <GC/GarbageCollector.h>
#include "Value.h"

namespace VM{
    inline Value makeFloatValue(double data) {
        return Value{{.fval=data}, ValueType::Float};
    }

    inline Value makeIntValue(int data) {
        return Value{{.ival=data}, ValueType::Int};
    }

    inline Value makeNullValue() {
        return Value{{.ival=0}, ValueType::None};
    }

    inline Value makeBoolValue(bool data) {
        return Value{{.bval=data}, ValueType::Bool};
    }

    inline Value makeStringObjValue(StringObj*data){
        return Value{{.sval=data},ValueType::String};
    }

    inline Value makeNativeFunctionObjValue(NativeFunctionObj*data){
        return Value{{.nfval=data},ValueType::NativeFunction};
    }

    inline Value makeDefinedFunctionObjValue(DefinedFunctionObj*data){
        return Value{{.dfval=data},ValueType::DefinedFunction};
    }

    inline double asFloat(const Value &value) {
        return value.data.fval;
    }

    inline int asInt(const Value &value) {
        return value.data.ival;
    }

    inline bool asBool(const Value &value) {
        return value.data.bval;
    }

    inline StringObj*asStringObj(const Value&value){
        return value.data.sval;
    }

    inline NativeFunctionObj* asNativeFunctionObj(const Value&value){
        return value.data.nfval;
    }

    inline DefinedFunctionObj* asDefinedFunctionObj(const Value&value){
        return value.data.dfval;
    }

    inline std::string toString(const Value &value) {
        switch (value.type) {
            case ValueType::None:
                return "None";

            case ValueType::Bool:
                if (asBool(value))
                    return "true";
                return "false";

            case ValueType::Float:
                return std::to_string(asFloat(value));

            case ValueType::Int:
                return std::to_string(asInt(value));

            case ValueType::String:
                return asStringObj(value)->data;
            case ValueType::NativeFunction:
                return "<built in function "+asNativeFunctionObj(value)->name+">";
            case ValueType::DefinedFunction:
                return "<function "+asDefinedFunctionObj(value)->name+">";
        }
    }


    inline bool isNumerical(const Value &value) {
        return value.type == ValueType::Float || value.type == ValueType::Int;
    }

    inline Value castToFloat(const Value &value) {
        switch (value.type) {
            case ValueType::Int:
                return makeFloatValue((double) asInt(value));
            case ValueType::Float:
                return value;
            default:
                throw std::runtime_error("Cannot cast " + typeToString(value.type) + " to Float");
        }
    }

    inline Value castToBool(const Value &value) {
        switch (value.type) {
            case ValueType::Int:
                return makeBoolValue((bool) asInt(value));
            case ValueType::Float:
                return makeBoolValue((bool) asFloat(value));
            case ValueType::Bool:
                return value;
            case ValueType::None:
                return makeBoolValue(false);
            default:
                throw std::runtime_error("Cannot cast " + typeToString(value.type) + " to Bool");
        }
    }

    inline Value castToInt(const Value &value) {
        switch (value.type) {
            case ValueType::Int:
                return value;
            case ValueType::Float:
                return makeIntValue((int) asFloat(value));
            default:
                throw std::runtime_error("Cannot cast " + typeToString(value.type) + " to Int");
        }
    }

    inline Value add(const Value &a, const Value &b) {

        if (isNumerical(a) && isNumerical(b)) {
            if (a.type == ValueType::Float || b.type == ValueType::Float) {
                return makeFloatValue(asFloat(castToFloat(a)) + asFloat(castToFloat(b)));
            }
            return makeIntValue(asInt(a) + asInt(b));

        }
        throw std::runtime_error(
                "Unsupported operand types for +: " + typeToString(a.type) + " and " + typeToString(b.type));
    }

    inline Value subtract(const Value &a, const Value &b) {

        if (isNumerical(a) && isNumerical(b)) {
            if (a.type == ValueType::Float || b.type == ValueType::Float) {
                return makeFloatValue(asFloat(castToFloat(a)) - asFloat(castToFloat(b)));
            }
            return makeIntValue(asInt(a) - asInt(b));
        }
        throw std::runtime_error(
                "Unsupported operand types for -: " + typeToString(a.type) + " and " + typeToString(b.type));
    }


    inline Value multiply(const Value &a, const Value &b) {
        if (isNumerical(a) && isNumerical(b)) {
            if (a.type == ValueType::Float || b.type == ValueType::Float) {
                return makeFloatValue(asFloat(castToFloat(a)) * asFloat(castToFloat(b)));
            }
            return makeIntValue(asInt(a) * asInt(b));
        }
        throw std::runtime_error(
                "Unsupported operand types for *: " + typeToString(a.type) + " and " + typeToString(b.type));
    }

    inline Value divide(const Value &a, const Value &b) {
        if (isNumerical(a) && isNumerical(b)) {
            return makeFloatValue(asFloat(castToFloat(a)) / asFloat(castToFloat(b)));
        }
        throw std::runtime_error(
                "Unsupported operand types for /: " + typeToString(a.type) + " and " + typeToString(b.type));
    }

    inline Value uminus(const Value &a) {
        if (a.type == ValueType::Int)
            return makeIntValue(-asInt(a));
        else if (a.type == ValueType::Float)
            return makeFloatValue(-asFloat(a));
        throw std::runtime_error("Unsupported operand for unary -: " + typeToString(a.type));
    }


    inline Value equal(const Value &a, const Value &b) {
        if (isNumerical(a) && isNumerical(b)) {
            if (a.type == ValueType::Float || b.type == ValueType::Float) {
                return makeBoolValue(asFloat(castToFloat(a)) == asFloat(castToFloat(b)));
            }
            return makeBoolValue(asInt(a) == asInt(b));

        } else if (a.type == b.type) {
            if (a.type == ValueType::Bool)
                return makeBoolValue(asBool(a) == asBool(b));
            else if (a.type == ValueType::None)
                return makeBoolValue(true);
        }

        throw std::runtime_error(
                "Unsupported operand types for ==: " + typeToString(a.type) + " and " + typeToString(b.type));
    }

    inline Value nequal(const Value &a, const Value &b) {
        if (isNumerical(a) && isNumerical(b)) {
            if (a.type == ValueType::Float || b.type == ValueType::Float) {
                return makeBoolValue(asFloat(castToFloat(a)) != asFloat(castToFloat(b)));
            }
            return makeBoolValue(asInt(a) != asInt(b));

        } else if (a.type == b.type) {
            if (a.type == ValueType::Bool)
                return makeBoolValue(asBool(a) != asBool(b));
            else if (a.type == ValueType::None)
                return makeBoolValue(false);
        }

        throw std::runtime_error(
                "Unsupported operand types for !=: " + typeToString(a.type) + " and " + typeToString(b.type));
    }

    inline Value greater(const Value &a, const Value &b) {
        if (isNumerical(a) && isNumerical(b)) {
            if (a.type == ValueType::Float || b.type == ValueType::Float) {
                return makeBoolValue(asFloat(castToFloat(a)) > asFloat(castToFloat(b)));
            }
            return makeBoolValue(asInt(a) > asInt(b));
        }

        throw std::runtime_error(
                "Unsupported operand types for >: " + typeToString(a.type) + " and " + typeToString(b.type));
    }

    inline Value less(const Value &a, const Value &b) {
        if (isNumerical(a) && isNumerical(b)) {
            if (a.type == ValueType::Float || b.type == ValueType::Float) {
                return makeBoolValue(asFloat(castToFloat(a)) < asFloat(castToFloat(b)));
            }
            return makeBoolValue(asInt(a) < asInt(b));
        }

        throw std::runtime_error(
                "Unsupported operand types for <: " + typeToString(a.type) + " and " + typeToString(b.type));
    }

    inline Value greatereq(const Value &a, const Value &b) {
        if (isNumerical(a) && isNumerical(b)) {
            if (a.type == ValueType::Float || b.type == ValueType::Float) {
                return makeBoolValue(asFloat(castToFloat(a)) >= asFloat(castToFloat(b)));
            }
            return makeBoolValue(asInt(a) >= asInt(b));
        }

        throw std::runtime_error(
                "Unsupported operand types for >=: " + typeToString(a.type) + " and " + typeToString(b.type));
    }

    inline Value lesseq(const Value &a, const Value &b) {
        if (isNumerical(a) && isNumerical(b)) {
            if (a.type == ValueType::Float || b.type == ValueType::Float) {
                return makeBoolValue(asFloat(castToFloat(a)) <= asFloat(castToFloat(b)));
            }
            return makeBoolValue(asInt(a) <= asInt(b));
        }

        throw std::runtime_error(
                "Unsupported operand types for <=: " + typeToString(a.type) + " and " + typeToString(b.type));
    }


    inline Value modulo(const Value &a, const Value &b) {
        if (a.type == ValueType::Int && b.type == ValueType::Int)
            return makeIntValue(asInt(a) % asInt(b));
        throw std::runtime_error(
                "Unsupported operand types for %: " + typeToString(a.type) + " and " + typeToString(b.type));


    }
}

#endif //INTERPRETER_ARITHMETIC_H
