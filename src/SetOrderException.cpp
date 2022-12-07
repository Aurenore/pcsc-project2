//
// Created by anyam on 07.12.2022.
//

#include "SetOrderException.h"

SetOrderException::SetOrderException(std::string probString) : Exception("SET_ORDER", probString) {}