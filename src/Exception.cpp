/*
 * Exception.cpp
 *
 *  Created on: Nov 15, 2012
 *      Author: rpopescu
 */

#include "Exception.hpp"
#include <iostream>

Exception::Exception(std::string tagString, std::string probString)
    : mTag(tagString), mProblem(probString) {
    /*!
   * Constructor of the Exception class

   * \param tagString: tag of the exception
     * \param probString: problem of the exception
   */
}

void Exception::PrintDebug() const {
    /*!
   * Prints the tag and the problem of the exception.
   */
  std::cerr << "** Error (" << mTag << ") **\n";
  std::cerr << "Problem: " << mProblem << "\n\n";
}
