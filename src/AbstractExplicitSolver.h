//
// Created by anyam on 30.11.2022.
//

#ifndef PCSC_PROJECT2_ABSTRACTEXPLICITSOLVER_H
#define PCSC_PROJECT2_ABSTRACTEXPLICITSOLVER_H

#include "AbstractOdeSolver.hpp"

/** Abstract class, daughter of AbstractOdeSolver, and mother class of
 * the classes which implement explicit methods to solve ODE, such as the Adam Bashforth method or Runke Kutta.
*/

class AbstractExplicitSolver : public AbstractOdeSolver{
public:
    AbstractExplicitSolver();
    AbstractExplicitSolver(const double h, const double t0, const double t1, const double y0,
                           double (*f)(double y, double t),const unsigned int s);
    virtual ~AbstractExplicitSolver();
    double GetB(const unsigned int i, const unsigned int j) const;
};


#endif //PCSC_PROJECT2_ABSTRACTEXPLICITSOLVER_H
