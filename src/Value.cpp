//
// Created by gvisan on 10.08.2020.
//

#include "Value.h"

namespace AST {
    Value::Value(int value) : type(Type::Int),data{.ival=value} {
    }

    Value::Value(double value) : type(Type::Float),data{.fval=value} {
    }

    Value::Value(const std::string &value) : type(Type::String),data{.sval=new std::string(value)} {
    }

    Value::Value() : type(Type::None),data() {

    }

    Value::~Value() {
        if (type == Type::String)
            delete data.sval;
    }

    void Value::swap(Value &other) {
        std::swap(data, other.data);
        std::swap(type, other.type);
    }

    Value::Value(const Value &other) : type(other.type),data() {
        switch (other.type) {
            case Type::String:
                data.sval = new std::string(*other.data.sval);
                break;
            default:
                //plain old data, just copy it
                data=other.data;
                break;
        }
    }

    Value &Value::operator=(Value other) {
        swap(other);
        return *this;
    }

    Value::Value(AST::Value &&other) noexcept:Value(){
        swap(other);
    }

    std::string Value::toString() const {
        switch (type) {
            case Type::None:
                return "None";
            case Type::String:
                return *data.sval;
            case Type::Int:
                return std::to_string(data.ival);
            case Type::Float:
                return std::to_string(data.fval);
        }
    }


    Value Value::operator+(const Value &other) const {
        switch (type) {
            case Type::Int:
                switch (other.type) {
                    case Type::Int:
                        return Value(data.ival + other.data.ival);
                    case Type::Float:
                        return Value(double(data.ival) + other.data.fval);
                    default:
                        break;
                }
                break;

            case Type::Float:
                switch (other.type) {
                    case Type::Int:
                        return Value(data.fval + (double) other.data.ival);
                    case Type::Float:
                        return Value(data.fval + other.data.fval);
                    default:
                        break;
                }
                break;

            case Type::String:
                switch (other.type) {
                    case Type::String:
                        return Value(*data.sval + *other.data.sval);
                    default:
                        break;
                }
                break;

            default:
                break;
        }
        throw std::runtime_error("Unsupported operand types for +: " + typeToString(type) + " and " + typeToString(other.type));
    }

    Value Value::operator-(const Value &other) const {
        switch (type) {
            case Type::Int:
                switch (other.type) {
                    case Type::Int:
                        return Value(data.ival - other.data.ival);
                    case Type::Float:
                        return Value(double(data.ival) - other.data.fval);
                    default:
                        break;
                }
                break;

            case Type::Float:
                switch (other.type) {
                    case Type::Int:
                        return Value(data.fval - (double) other.data.ival);
                    case Type::Float:
                        return Value(data.fval - other.data.fval);
                    default:
                        break;
                }
                break;

            default:
                break;
        }
        throw std::runtime_error("Unsupported operand types for -: " + typeToString(type) + " and " + typeToString(other.type));
    }

    Value Value::operator*(const Value &other) const {
        switch (type) {
            case Type::Int:
                switch (other.type) {
                    case Type::Int:
                        return Value(data.ival * other.data.ival);
                    case Type::Float:
                        return Value(double(data.ival) * other.data.fval);
                    default:
                        break;
                }
                break;

            case Type::Float:
                switch (other.type) {
                    case Type::Int:
                        return Value(data.fval * (double) other.data.ival);
                    case Type::Float:
                        return Value(data.fval * other.data.fval);
                    default:
                        break;
                }
                break;

            default:
                break;
        }
        throw std::runtime_error("Unsupported operand types for *: " + typeToString(type) + " and " + typeToString(other.type));
    }

    Value Value::operator/(const Value &other) const {
        switch (type) {
            case Type::Int:
                switch (other.type) {
                    case Type::Int:
                        return Value((double) data.ival / (double) other.data.ival);
                    case Type::Float:
                        return Value(double(data.ival) / other.data.fval);
                    default:
                        break;
                }
                break;

            case Type::Float:
                switch (other.type) {
                    case Type::Int:
                        return Value(data.fval / (double) other.data.ival);
                    case Type::Float:
                        return Value(data.fval / other.data.fval);
                    default:
                        break;
                }
                break;

            default:
                break;
        }
        throw std::runtime_error("Unsupported operand types for /: " + typeToString(type) + " and " + typeToString(other.type));
    }

    Value Value::operator-() const {
        switch(type){
            case Type ::Int:
                return Value(-data.ival);
            case Type::Float:
                return Value(-data.fval);
            default:
                throw std::runtime_error("Unsupported operand for unary -: "+typeToString(type));
        }
    }

    Type Value::getType() const {
        return type;
    }
}