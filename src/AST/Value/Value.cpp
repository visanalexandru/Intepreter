//
// Created by gvisan on 10.08.2020.
//

#include "Value.h"

namespace AST {
    Value::Value(int value) : type(Type::Int), data{.ival=value} {
    }

    Value::Value(double value) : type(Type::Float), data{.fval=value} {
    }

    Value::Value(const std::string &value) : type(Type::String), data{.sval=new std::string(value)} {
    }

    Value::Value(bool value) : type(Type::Bool), data{.bval=value} {

    }

    Value::Value() : type(Type::None), data() {

    }

    Value::~Value() {
        if (type == Type::String)
            delete data.sval;
    }

    void Value::swap(Value &other) {
        std::swap(data, other.data);
        std::swap(type, other.type);
    }

    Value::Value(const Value &other) : type(other.type), data() {
        switch (other.type) {
            case Type::String:
                data.sval = new std::string(other.asString());
                break;
            default:
                //plain old data, just copy it
                data = other.data;
                break;
        }
    }

    Value &Value::operator=(Value other) {
        swap(other);
        return *this;
    }

    Value::Value(AST::Value &&other) noexcept: Value() {
        swap(other);
    }

    std::string Value::toString() const {
        switch (type) {
            case Type::None:
                return "None";
            case Type::String:
                return asString();
            case Type::Int:
                return std::to_string(asInt());
            case Type::Float:
                return std::to_string(asFloat());
            case Type::Bool:
                if (asBool())
                    return "true";
                return "false";
        }
    }

    bool Value::isNumerical() const {
        return type == Type::Float || type == Type::Int;
    }

    Value Value::toFloatObj() const {
        switch (type) {
            case Type::Int:
                return Value((double) asInt());
            case Type::Float:
                return Value(asFloat());
            default:
                break;
        }
        throw std::runtime_error("Cannot convert " + typeToString(type) + " to Float");
    }

    Value Value::toIntObj() const {
        switch (type) {
            case Type::Int:
                return Value(asInt());
            case Type::Float:
                return Value((int) asFloat());
            default:
                break;
        }
        throw std::runtime_error("Cannot convert " + typeToString(type) + " to Int");
    }

    Value Value::toStringObj() const {
        return Value(toString());
    }

    Value Value::toBoolObj() const {
        switch (type) {
            case Type::Int:
                return Value((bool) asInt());
            case Type::Float:
                return Value((bool) asFloat());
            case Type::String:
                return Value(!asString().empty());
            case Type::Bool:
                return Value(asBool());
            case Type::None:
                return Value(false);
        }
    }

    int Value::asInt() const {
        return data.ival;
    }

    double Value::asFloat() const {
        return data.fval;
    }

    std::string Value::asString() const {
        return *data.sval;
    }

    bool Value::asBool() const {
        return data.bval;
    }


    Value Value::operator+(const Value &other) const {
        if (isNumerical() && other.isNumerical()) {
            if (other.type == Type::Float || type == Type::Float) {
                return Value(toFloatObj().asFloat() + other.toFloatObj().asFloat());
            }
            return Value(asInt() + other.asInt());
        } else if (type == Type::String && other.type == Type::String) {
            return Value(asString() + other.asString());
        }

        throw std::runtime_error(
                "Unsupported operand types for +: " + typeToString(type) + " and " + typeToString(other.type));
    }

    Value Value::operator-(const Value &other) const {
        if (isNumerical() && other.isNumerical()) {
            if (other.type == Type::Float || type == Type::Float) {
                return Value(toFloatObj().asFloat() - other.toFloatObj().asFloat());
            }
            return Value(asInt() - other.asInt());
        }
        throw std::runtime_error(
                "Unsupported operand types for -: " + typeToString(type) + " and " + typeToString(other.type));
    }

    Value Value::operator*(const Value &other) const {
        if (isNumerical() && other.isNumerical()) {
            if (other.type == Type::Float || type == Type::Float) {
                return Value(toFloatObj().asFloat() * other.toFloatObj().asFloat());
            }
            return Value(asInt()* other.asInt());
        }

        throw std::runtime_error(
                "Unsupported operand types for *: " + typeToString(type) + " and " + typeToString(other.type));
    }

    Value Value::operator/(const Value &other) const {
        if (isNumerical() && other.isNumerical()) {
            return Value(toFloatObj().asFloat() / other.toFloatObj().asFloat());
        }
        throw std::runtime_error(
                "Unsupported operand types for /: " + typeToString(type) + " and " + typeToString(other.type));
    }

    Value Value::operator-() const {
        if (type == Type::Int)
            return Value(-asInt());
        else if (type == Type::Float)
            return Value(-asFloat());
        throw std::runtime_error("Unsupported operand for unary -: " + typeToString(type));
    }

    Value Value::operator==(const Value &other) const {
        if (isNumerical() && other.isNumerical()) {
            if (other.type == Type::Float || type == Type::Float) {
                return Value(toFloatObj().asFloat() == other.toFloatObj().asFloat());
            }
            return Value(asInt() == other.asInt());

        } else if (type == other.type) {
            if (type == Type::String)
                return Value(asString() == other.asString());
            else if (type == Type::Bool)
                return Value(asBool()== other.asBool());
        }

        throw std::runtime_error(
                "Unsupported operand types for ==: " + typeToString(type) + " and " + typeToString(other.type));
    }

    Value Value::operator!=(const Value &other) const {
        if (isNumerical() && other.isNumerical()) {
            if (other.type == Type::Float || type == Type::Float) {
                return Value(toFloatObj().asFloat() != other.toFloatObj().asFloat());
            }
            return Value(asInt() != other.asInt());

        } else if (type == other.type) {
            if (type == Type::String)
                return Value(asString() != other.asString());
            else if (type == Type::Bool)
                return Value(asBool()!= other.asBool());
        }

        throw std::runtime_error(
                "Unsupported operand types for !=: " + typeToString(type) + " and " + typeToString(other.type));
    }

    Value Value::operator>(const Value &other) const {
        if (isNumerical() && other.isNumerical()) {
            if (other.type == Type::Float || type == Type::Float) {
                return Value(toFloatObj().asFloat() > other.toFloatObj().asFloat());
            }
            return Value(asInt()> other.asInt());
        }

        throw std::runtime_error(
                "Unsupported operand types for >: " + typeToString(type) + " and " + typeToString(other.type));
    }

    Value Value::operator<(const Value &other) const {

        if (isNumerical() && other.isNumerical()) {
            if (other.type == Type::Float || type == Type::Float) {
                return Value(toFloatObj().asFloat() < other.toFloatObj().asFloat());
            }
            return Value(asInt() < other.asInt());
        }

        throw std::runtime_error(
                "Unsupported operand types for <: " + typeToString(type) + " and " + typeToString(other.type));

    }

    Value Value::operator>=(const Value &other) const {
        if (isNumerical() && other.isNumerical()) {
            if (other.type == Type::Float || type == Type::Float) {
                return Value(toFloatObj().asFloat() >= other.toFloatObj().asFloat());
            }
            return Value(asInt()>= other.asInt());
        }

        throw std::runtime_error(
                "Unsupported operand types for >=: " + typeToString(type) + " and " + typeToString(other.type));

    }

    Value Value::operator<=(const Value &other) const {
        if (isNumerical() && other.isNumerical()) {
            if (other.type == Type::Float || type == Type::Float) {
                return Value(toFloatObj().asFloat() <= other.toFloatObj().asFloat());
            }
            return Value(asInt() <=other.asInt());
        }

        throw std::runtime_error(
                "Unsupported operand types for <=: " + typeToString(type) + " and " + typeToString(other.type));
    }

    Value Value::operator%(const Value&other) const{
        if(type==Type::Int && other.type==Type::Int)
            return Value(asInt()%other.asInt());
        throw std::runtime_error("Unsupported operand types for %: " + typeToString(type) + " and " + typeToString(other.type));
    }

    Type Value::getType() const {
        return type;
    }
}