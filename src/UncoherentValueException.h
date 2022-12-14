//
// Created by anyam on 09.12.2022.
//

#ifndef PCSC_PROJECT_UNCOHERENTVALUEEXCEPTION_H
#define PCSC_PROJECT_UNCOHERENTVALUEEXCEPTION_H

#include "Exception.hpp"

/** Daughter of Exception class. Is thrown when a value is uncoherent. */
class UncoherentValueException : public Exception{
public:
    UncoherentValueException(std::string probString);

};


#endif //PCSC_PROJECT_UNCOHERENTVALUEEXCEPTION_H
