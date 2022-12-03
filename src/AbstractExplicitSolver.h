//
// Created by anyam on 30.11.2022.
//

#ifndef PCSC_PROJECT2_ABSTRACTEXPLICITSOLVER_H
#define PCSC_PROJECT2_ABSTRACTEXPLICITSOLVER_H

#include "AbstractOdeSolver.hpp"

class AbstractExplicitSolver : public AbstractOdeSolver{
public:
    AbstractExplicitSolver();
    AbstractExplicitSolver(const double h, const double t0, const double t1, const double y0,
                           double (*f)(double y, double t),const unsigned int s);
    virtual ~AbstractExplicitSolver();
};


#endif //PCSC_PROJECT2_ABSTRACTEXPLICITSOLVER_H