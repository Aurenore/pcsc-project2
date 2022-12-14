//
// Created by anyam on 07.12.2022.
//

#ifndef PCSC_PROJECT_OUTOFRANGEEXCEPTION_H
#define PCSC_PROJECT_OUTOFRANGEEXCEPTION_H

#include "Exception.hpp"
/** Daughter of Exception class. Is thrown when the indices are out of scope.*/
class OutOfRangeException : public Exception{
public:
    OutOfRangeException(std::string probString);
};


#endif //PCSC_PROJECT_OUTOFRANGEEXCEPTION_H
