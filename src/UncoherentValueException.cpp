//
// Created by anyam on 09.12.2022.
//

#include "UncoherentValueException.h"

UncoherentValueException::UncoherentValueException(std::string probString) : Exception("UNCOHERENT_VALUE", probString){}