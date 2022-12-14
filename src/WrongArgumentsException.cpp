//
// Created by anyam on 14.12.2022.
//

#include "WrongArgumentsException.h"

WrongArgumentsException::WrongArgumentsException(std::string probString)
        : Exception("WRONG_ARGUMENTS", probString) {}