//
// Created by anyam on 05.12.2022.
//

#include "UnsetOrderException.h"

UnsetOrderException::UnsetOrderException(std::string probString)
    : Exception("UNSET_ORDER", probString) {}
