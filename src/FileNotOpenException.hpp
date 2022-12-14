/*
 * FileNonOpenException.hpp
 *
 *  Created on: Nov 15, 2012
 *      Author: rpopescu
 */

#ifndef FILENOTOPENEXCEPTIONDEF
#define FILENOTOPENEXCEPTIONDEF

#include "Exception.hpp"
#include <string>
/** Daughter of Exception class. Is thrown when a file cannot be opened.*/
class FileNotOpenException : public Exception {
public:
  FileNotOpenException(std::string probString);
};

#endif // FILENOTOPENEXCEPTIONDEF
