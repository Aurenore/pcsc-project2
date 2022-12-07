/*
 * FileNotOpenException.cpp
 *
 *  Created on: Nov 15, 2012
 *      Author: rpopescu
 */

#include "FileNotOpenException.hpp"
#include <iostream>

// Constructor
FileNotOpenException::FileNotOpenException(std::string probString)
    : Exception("FILE_NOT_OPEN", probString) {}
