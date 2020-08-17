//
// Created by gvisan on 11.08.2020.
//
#define CATCH_CONFIG_MAIN
#include"catch.hpp"
#include "AST/Value/Value.h"
#include "AST/Context.h"

TEST_CASE("Integer arithmetic","[arithmetic]"){

    AST::Value result;
    //INT INT
    REQUIRE_NOTHROW(result=AST::Value(100)+AST::Value(20));
    REQUIRE(result.toString()=="120");
    REQUIRE(result.getType()==AST::Type::Int);

    REQUIRE_NOTHROW(result=AST::Value(23)-AST::Value(20));
    REQUIRE(result.toString()=="3");
    REQUIRE(result.getType()==AST::Type::Int);

    REQUIRE_NOTHROW(result=AST::Value(3)*AST::Value(4));
    REQUIRE(result.toString()=="12");
    REQUIRE(result.getType()==AST::Type::Int);

    REQUIRE_NOTHROW(result=AST::Value(6)/AST::Value(2));
    REQUIRE(result.toString()=="3.000000");
    REQUIRE(result.getType()==AST::Type::Float);

    REQUIRE_NOTHROW(result=AST::Value(6)==AST::Value(3));
    REQUIRE(result.toString()=="false");
    REQUIRE(result.getType()==AST::Type::Bool);

    REQUIRE_NOTHROW(result=AST::Value(20)==AST::Value(20));
    REQUIRE(result.toString()=="true");
    REQUIRE(result.getType()==AST::Type::Bool);

    //INT FLOAT
    REQUIRE_NOTHROW(result=AST::Value(6)+AST::Value(3.2));
    REQUIRE(result.toString()=="9.200000");
    REQUIRE(result.getType()==AST::Type::Float);

    REQUIRE_NOTHROW(result=AST::Value(20)-AST::Value(60.0));
    REQUIRE(result.toString()=="-40.000000");
    REQUIRE(result.getType()==AST::Type::Float);

    REQUIRE_NOTHROW(result=AST::Value(20)*AST::Value(2.5));
    REQUIRE(result.toString()=="50.000000");
    REQUIRE(result.getType()==AST::Type::Float);

    REQUIRE_NOTHROW(result=AST::Value(125)/AST::Value(10.4));
    REQUIRE(result.toString()=="12.019231");
    REQUIRE(result.getType()==AST::Type::Float);

    REQUIRE_NOTHROW(result=AST::Value(100)==AST::Value(100.003));
    REQUIRE(result.toString()=="false");
    REQUIRE(result.getType()==AST::Type::Bool);

    REQUIRE_NOTHROW(result=AST::Value(5123)==AST::Value(5123.00));
    REQUIRE(result.toString()=="true");
    REQUIRE(result.getType()==AST::Type::Bool);

    //UMINUS INT
    REQUIRE_NOTHROW(result=-AST::Value(4));
    REQUIRE(result.toString()=="-4");
    REQUIRE(result.getType()==AST::Type::Int);


    //INT STRING
    REQUIRE_THROWS_WITH(AST::Value(410)+AST::Value(std::string("first")),"Unsupported operand types for +: Int and String");
    REQUIRE_THROWS_WITH(AST::Value(232)-AST::Value(std::string("second")),"Unsupported operand types for -: Int and String");
    REQUIRE_THROWS_WITH(AST::Value(2)*AST::Value(std::string("test")),"Unsupported operand types for *: Int and String");
    REQUIRE_THROWS_WITH(AST::Value(2322)/AST::Value(std::string("a")),"Unsupported operand types for /: Int and String");
    REQUIRE_THROWS_WITH(AST::Value(100)==AST::Value(std::string("100")),"Unsupported operand types for ==: Int and String");
}



TEST_CASE("Float arithmetic","[arithmetic]"){

AST::Value result;
//FLOAT INT
REQUIRE_NOTHROW(result=AST::Value(79.23)+AST::Value(20));
REQUIRE(result.toString()=="99.230000");
REQUIRE(result.getType()==AST::Type::Float);

REQUIRE_NOTHROW(result=AST::Value(42.323)-AST::Value(20));
REQUIRE(result.toString()=="22.323000");
REQUIRE(result.getType()==AST::Type::Float);

REQUIRE_NOTHROW(result=AST::Value(3.3)*AST::Value(4));
REQUIRE(result.toString()=="13.200000");
REQUIRE(result.getType()==AST::Type::Float);

REQUIRE_NOTHROW(result=AST::Value(122.823)/AST::Value(2));
REQUIRE(result.toString()=="61.411500");
REQUIRE(result.getType()==AST::Type::Float);

REQUIRE_NOTHROW(result=AST::Value(64.123)==AST::Value(100));
REQUIRE(result.toString()=="false");
REQUIRE(result.getType()==AST::Type::Bool);

REQUIRE_NOTHROW(result=AST::Value(100.000)==AST::Value(100));
REQUIRE(result.toString()=="true");
REQUIRE(result.getType()==AST::Type::Bool);

//FLOAT FLOAT
REQUIRE_NOTHROW(result=AST::Value(26.88)+AST::Value(3.2));
REQUIRE(result.toString()=="30.080000");
REQUIRE(result.getType()==AST::Type::Float);

REQUIRE_NOTHROW(result=AST::Value(4.3)-AST::Value(1.2));
REQUIRE(result.toString()=="3.100000");
REQUIRE(result.getType()==AST::Type::Float);

REQUIRE_NOTHROW(result=AST::Value(10.0)*AST::Value(4.0));
REQUIRE(result.toString()=="40.000000");
REQUIRE(result.getType()==AST::Type::Float);

REQUIRE_NOTHROW(result=AST::Value(43.5)/AST::Value(10.4));
REQUIRE(result.toString()=="4.182692");
REQUIRE(result.getType()==AST::Type::Float);

REQUIRE_NOTHROW(result=AST::Value(64.123)==AST::Value(123.421));
REQUIRE(result.toString()=="false");
REQUIRE(result.getType()==AST::Type::Bool);

REQUIRE_NOTHROW(result=AST::Value(3.1415)==AST::Value(3.1415));
REQUIRE(result.toString()=="true");
REQUIRE(result.getType()==AST::Type::Bool);

//UMINUS FLOAT
REQUIRE_NOTHROW(result=-AST::Value(-23.44));
REQUIRE(result.toString()=="23.440000");
REQUIRE(result.getType()==AST::Type::Float);

//FLOAT STRING
REQUIRE_THROWS_WITH(AST::Value(2.3)+AST::Value(std::string("string")),"Unsupported operand types for +: Float and String");
REQUIRE_THROWS_WITH(AST::Value(4.5)-AST::Value(std::string("test")),"Unsupported operand types for -: Float and String");
REQUIRE_THROWS_WITH(AST::Value(123.4)*AST::Value(std::string("hhfffa")),"Unsupported operand types for *: Float and String");
REQUIRE_THROWS_WITH(AST::Value(0.23)/AST::Value(std::string("a")),"Unsupported operand types for /: Float and String");
REQUIRE_THROWS_WITH(AST::Value(64.234)==AST::Value(std::string("test")),"Unsupported operand types for ==: Float and String");
}




TEST_CASE("String arithmetic","[arithmetic]"){
//STRING INT
REQUIRE_THROWS_WITH(AST::Value(std::string("string"))+AST::Value(54),"Unsupported operand types for +: String and Int");
REQUIRE_THROWS_WITH(AST::Value(std::string("test"))-AST::Value(27),"Unsupported operand types for -: String and Int");
REQUIRE_THROWS_WITH(AST::Value(std::string("arithmetic"))*AST::Value(4),"Unsupported operand types for *: String and Int");
REQUIRE_THROWS_WITH(AST::Value(std::string("debug"))/AST::Value(54),"Unsupported operand types for /: String and Int");
REQUIRE_THROWS_WITH(AST::Value(std::string("100"))==AST::Value(100),"Unsupported operand types for ==: String and Int");
//STRING FLOAT
REQUIRE_THROWS_WITH(AST::Value(std::string("string"))+AST::Value(420.69),"Unsupported operand types for +: String and Float");
REQUIRE_THROWS_WITH(AST::Value(std::string("test"))-AST::Value(58.22),"Unsupported operand types for -: String and Float");
REQUIRE_THROWS_WITH(AST::Value(std::string("arithmetic"))*AST::Value(.232),"Unsupported operand types for *: String and Float");
REQUIRE_THROWS_WITH(AST::Value(std::string("debug"))/AST::Value(2323.0),"Unsupported operand types for /: String and Float");
REQUIRE_THROWS_WITH(AST::Value(std::string("23.34"))==AST::Value(23.34),"Unsupported operand types for ==: String and Float");
//UMINUS STRING
REQUIRE_THROWS_WITH(-AST::Value(std::string("test")),"Unsupported operand for unary -: String");

//STRING STRING
AST::Value value;
REQUIRE_NOTHROW(value=AST::Value(std::string("hello "))+AST::Value(std::string("world")));
REQUIRE(value.toString()=="hello world");

REQUIRE_NOTHROW(value=AST::Value(std::string("test"))==AST::Value(std::string("tester")));
REQUIRE(value.toString()=="false");
REQUIRE(value.getType()==AST::Type::Bool);

REQUIRE_NOTHROW(value=AST::Value(std::string("this is a test"))==AST::Value(std::string("this is a test")));
REQUIRE(value.toString()=="true");
REQUIRE(value.getType()==AST::Type::Bool);

REQUIRE_THROWS_WITH(AST::Value(std::string("hxc"))-AST::Value(std::string("axcv")),"Unsupported operand types for -: String and String");
REQUIRE_THROWS_WITH(AST::Value(std::string("ar"))*AST::Value(std::string("axx")),"Unsupported operand types for *: String and String");
REQUIRE_THROWS_WITH(AST::Value(std::string("stack"))/AST::Value(std::string("overflow")),"Unsupported operand types for /: String and String");

}



TEST_CASE("Variables","[context]"){
    AST::Context context;

    SECTION("Variable declaration"){
        context.declareVar("data",AST::Value(200));
        REQUIRE(context.getVar("data").toString()=="200");
        SECTION("Variable already defined in current scope"){
            REQUIRE_THROWS_WITH(context.declareVar("data",AST::Value(23.f)),"Variable has already been declared in this scope: data");
        }
        SECTION("Variable not defined"){
            REQUIRE_THROWS_WITH(context.getVar("stack"),"Variable has not been declared: stack");
        }
        SECTION("Multiple scopes"){
            context.pushScope();
            REQUIRE_NOTHROW(context.declareVar("data",AST::Value("test")));
            context.declareVar("test",AST::Value(23));
            context.popScope();
            REQUIRE_THROWS_WITH(context.getVar("test"),"Variable has not been declared: test");
        }

    }
    SECTION("Variable assignment"){
        context.declareVar("astest",AST::Value(2.f));
        SECTION("Simple assignment"){
            REQUIRE_NOTHROW(context.setVar("astest",AST::Value(20)));
            REQUIRE(context.getVar("astest").toString()=="20");
        }
        SECTION("Variable not defined"){
            REQUIRE_THROWS_WITH(context.setVar("unknown",AST::Value(2333)),"Variable has not been declared: unknown");
        }
        SECTION("Multiple scopes"){
            context.pushScope();
            REQUIRE_NOTHROW(context.setVar("astest",AST::Value(2323)));
            context.declareVar("hhh",AST::Value("not"));
            context.popScope();
            REQUIRE_THROWS_WITH(context.setVar("hhh",AST::Value("ok")),"Variable has not been declared: hhh");
        }
}

}