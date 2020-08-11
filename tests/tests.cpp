//
// Created by gvisan on 11.08.2020.
//
#define CATCH_CONFIG_MAIN
#include"catch.hpp"
#include "Value.h"

TEST_CASE("Value operators","[value]"){
    AST::Value ival(100),fval(200.f),sval("test");
    REQUIRE(ival.toString()=="100");
}