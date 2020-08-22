//
// Created by gvisan on 18.08.2020.
//

#ifndef INTERPRETER_ERROR_H
#define INTERPRETER_ERROR_H

#include<string>
#include <sstream>
#include <location.hh>


class Error {
private:
    yy::location location;
    std::string message;
public:
    Error(std::string error, yy::location loc);

    void log() const;

    std::string toString() const;
};


#endif //INTERPRETER_ERROR_H
