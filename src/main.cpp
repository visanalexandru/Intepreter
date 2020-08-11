//
// Created by gvisan on 10.08.2020.
//
#include "Driver.h"
#include "Value.h"
int main(int argc,char**argv){
    Driver driver;
    int success=driver.parse("test.lang");
    if(success==0)
        std::cout<<(driver.result).toString();
    return 0;
}