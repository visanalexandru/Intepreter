//
// Created by gvisan on 10.08.2020.
//
#include "Driver.h"
#include "Value.h"
int main(int argc,char**argv){
    Driver driver;
    driver.parse("test.lang");
    std::cout<<driver.result;
    return 0;
}