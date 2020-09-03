//
// Created by gvisan on 10.08.2020.
//
#include "Driver.h"

int main(int argc, char **argv) {
    Driver driver;
    driver.parse("test.lang");
    driver.start();

   return 0;
}