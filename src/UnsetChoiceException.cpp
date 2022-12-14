//
// Created by anyam on 14.12.2022.
//

#include "UnsetChoiceException.h"

UnsetChoiceException::UnsetChoiceException(std::string probString)
        : Exception("UNSET_CHOICE", probString) {}