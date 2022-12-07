//
// Created by anyam on 07.12.2022.
//

#ifndef PCSC_PROJECT_SETORDEREXCEPTION_H
#define PCSC_PROJECT_SETORDEREXCEPTION_H

#include "Exception.hpp"

class SetOrderException : public Exception {
public:
    SetOrderException(std::string probString);
};


#endif //PCSC_PROJECT_SETORDEREXCEPTION_H
