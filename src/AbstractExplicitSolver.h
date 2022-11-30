//
// Created by anyam on 30.11.2022.
//

#ifndef PCSC_PROJECT2_ABSTRACTEXPLICITSOLVER_H
#define PCSC_PROJECT2_ABSTRACTEXPLICITSOLVER_H

#include "AbstractOdeSolver.hpp"

class AbstractExplicitSolver : public AbstractOdeSolver{
public:
    AbstractExplicitSolver();
    virtual ~AbstractExplicitSolver();
};


#endif //PCSC_PROJECT2_ABSTRACTEXPLICITSOLVER_H
