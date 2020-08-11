//
// Created by gvisan on 11.08.2020.
//
#define CATCH_CONFIG_MAIN
#include"catch.hpp"
#include "Value.h"

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


    //INT STRING
    REQUIRE_THROWS_WITH(AST::Value(410)+AST::Value("first"),"Unsupported operand types for +: Int and String");
    REQUIRE_THROWS_WITH(AST::Value(232)-AST::Value("second"),"Unsupported operand types for -: Int and String");
    REQUIRE_THROWS_WITH(AST::Value(2)*AST::Value("test"),"Unsupported operand types for *: Int and String");
    REQUIRE_THROWS_WITH(AST::Value(2322)/AST::Value("a"),"Unsupported operand types for /: Int and String");
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


//FLOAT STRING
REQUIRE_THROWS_WITH(AST::Value(2.3)+AST::Value("string"),"Unsupported operand types for +: Float and String");
REQUIRE_THROWS_WITH(AST::Value(4.5)-AST::Value("test"),"Unsupported operand types for -: Float and String");
REQUIRE_THROWS_WITH(AST::Value(123.4)*AST::Value("hhfffa"),"Unsupported operand types for *: Float and String");
REQUIRE_THROWS_WITH(AST::Value(0.23)/AST::Value("a"),"Unsupported operand types for /: Float and String");
}




TEST_CASE("String arithmetic","[arithmetic]"){
//STRING INT
REQUIRE_THROWS_WITH(AST::Value("string")+AST::Value(54),"Unsupported operand types for +: String and Int");
REQUIRE_THROWS_WITH(AST::Value("test")-AST::Value(27),"Unsupported operand types for -: String and Int");
REQUIRE_THROWS_WITH(AST::Value("arithmetic")*AST::Value(4),"Unsupported operand types for *: String and Int");
REQUIRE_THROWS_WITH(AST::Value("debug")/AST::Value(54),"Unsupported operand types for /: String and Int");

//STRING FLOAT
REQUIRE_THROWS_WITH(AST::Value("string")+AST::Value(420.69),"Unsupported operand types for +: String and Float");
REQUIRE_THROWS_WITH(AST::Value("test")-AST::Value(58.22),"Unsupported operand types for -: String and Float");
REQUIRE_THROWS_WITH(AST::Value("arithmetic")*AST::Value(.232),"Unsupported operand types for *: String and Float");
REQUIRE_THROWS_WITH(AST::Value("debug")/AST::Value(2323.0),"Unsupported operand types for /: String and Float");

//STRING STRING
AST::Value value;
REQUIRE_NOTHROW(value=AST::Value("hello ")+AST::Value("world"));
REQUIRE(value.toString()=="hello world");

REQUIRE_THROWS_WITH(AST::Value("hxc")-AST::Value("axcv"),"Unsupported operand types for -: String and String");
REQUIRE_THROWS_WITH(AST::Value("ar")*AST::Value("axx"),"Unsupported operand types for *: String and String");
REQUIRE_THROWS_WITH(AST::Value("stack")/AST::Value("overflow"),"Unsupported operand types for /: String and String");

}
