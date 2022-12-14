//
// Created by anyam on 14.12.2022.
//

#ifndef PCSC_PROJECT_WRONGARGUMENTSEXCEPTION_H
#define PCSC_PROJECT_WRONGARGUMENTSEXCEPTION_H

#include "Exception.hpp"
#include <string>

class WrongArgumentsException : public Exception{
public:
    WrongArgumentsException(std::string probString);
};


#endif //PCSC_PROJECT_WRONGARGUMENTSEXCEPTION_H
