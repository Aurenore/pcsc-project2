//
// Created by anyam on 05.12.2022.
//

#ifndef PCSC_PROJECT_UNSETORDEREXCEPTION_H
#define PCSC_PROJECT_UNSETORDEREXCEPTION_H

#include "Exception.hpp"
/** Unset Order Exception class : daughter of Exception class. Exception thrown when the order is not set.*/
class UnsetOrderException : public Exception {
public:
    UnsetOrderException(std::string probString);
};


#endif //PCSC_PROJECT_UNSETORDEREXCEPTION_H
