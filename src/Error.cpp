//
// Created by gvisan on 18.08.2020.
//

#include "Error.h"

Error::Error(std::string error, yy::location loc) :
        message(std::move(error)),
        location(loc)
        {


}

void Error::log() const {
    std::cerr << location << ": " << message << '\n';
}

std::string Error::toString() const {
    std::ostringstream stream;
    stream<<location<<": "<<message<<'\n';
    return stream.str();
}
