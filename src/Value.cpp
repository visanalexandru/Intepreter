//
// Created by gvisan on 10.08.2020.
//

#include "Value.h"

namespace AST {
    Value::Value(int value) : type(Type::Int), data{.ival=value} {
    }

    Value::Value(float value) : type(Type::Float), data{.fval=value} {
    }

    Value::Value(const std::string &value) : type(Type::String), data{.sval=new std::string(value)} {
    }

    Value::Value() : type(Type::None) {

    }

    Value::~Value() {
        if (type == Type::String)
            delete data.sval;
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
                        return Value(float(data.ival) + other.data.fval);
                }
            case Type::Float:
                switch (other.type) {
                    case Type::Int:
                        return Value(data.fval + (float) other.data.ival);
                    case Type::Float:
                        return Value(data.fval + other.data.fval);
                }

            case Type::String:
                switch (other.type) {
                    case Type::String:
                        return Value(*data.sval + *other.data.sval);
                }
        }
        throw std::runtime_error("Cannot add " + typeToString(other.type) + " to " + typeToString(type));
    }

    Value Value::operator-(const Value &other) const {
        switch (type) {
            case Type::Int:
                switch (other.type) {
                    case Type::Int:
                        return Value(data.ival - other.data.ival);
                    case Type::Float:
                        return Value(float(data.ival) - other.data.fval);
                }
            case Type::Float:
                switch (other.type) {
                    case Type::Int:
                        return Value(data.fval - (float) other.data.ival);
                    case Type::Float:
                        return Value(data.fval - other.data.fval);
                }
        }
        throw std::runtime_error("Cannot subtract " + typeToString(other.type) + " from " + typeToString(type));
    }

    Value Value::operator*(const Value &other) const {
        switch (type) {
            case Type::Int:
                switch (other.type) {
                    case Type::Int:
                        return Value(data.ival * other.data.ival);
                    case Type::Float:
                        return Value(float(data.ival) * other.data.fval);
                }
            case Type::Float:
                switch (other.type) {
                    case Type::Int:
                        return Value(data.fval * (float) other.data.ival);
                    case Type::Float:
                        return Value(data.fval * other.data.fval);
                }
        }
        throw std::runtime_error("Cannot multiply " + typeToString(other.type) + " by " + typeToString(type));
    }

    Value Value::operator/(const Value &other) const {
        switch (type) {
            case Type::Int:
                switch (other.type) {
                    case Type::Int:
                        return Value((float) data.ival / (float) other.data.ival);
                    case Type::Float:
                        return Value(float(data.ival) / other.data.fval);
                }
            case Type::Float:
                switch (other.type) {
                    case Type::Int:
                        return Value(data.fval / (float) other.data.ival);
                    case Type::Float:
                        return Value(data.fval / other.data.fval);
                }
        }
        throw std::runtime_error("Cannot divide " + typeToString(other.type) + " by " + typeToString(type));
    }
}