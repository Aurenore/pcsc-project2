//
// Created by anyam on 14.12.2022.
//

#ifndef PCSC_PROJECT_UNSETCHOICEEXCEPTION_H
#define PCSC_PROJECT_UNSETCHOICEEXCEPTION_H

#include "Exception.hpp"

/** Daughter of Exception class. Exception thrown when the choice is not set.*/

class UnsetChoiceException : public Exception{
public:
    UnsetChoiceException(std::string probString);
};


#endif //PCSC_PROJECT_UNSETCHOICEEXCEPTION_H
