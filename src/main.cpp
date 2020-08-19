//
// Created by gvisan on 10.08.2020.
//
#include "Driver.h"
#include "AST/Value/Value.h"

int main(int argc, char **argv) {
    Driver driver;
    int success = driver.parse("test.lang");
    driver.semanticAnalysis();


    if (driver.errors.empty()) {
        std::cout << "Parsing successful" << std::endl;
        float a = clock();
        for (const auto &stmt : driver.result)
            stmt->execute();
        std::cout << "Took " << (clock() - a) / CLOCKS_PER_SEC << std::endl;
    }
    else {
        std::cerr<<"Errors:"<<std::endl;
        for(const Error&error:driver.errors)
            error.log();
    }
   return 0;
}