//
// Created by anyam on 30.11.2022.
//

#ifndef ABSTRACTIMPLICITSOLVERHEADERDEF
#define ABSTRACTIMPLICITSOLVERHEADERDEF

#include "AbstractOdeSolver.hpp"

/** Abstract class, daughter of AbstractOdeSolver, and mother class of the classes
 * which implement implicit methods to solve ODE.
 */
class AbstractImplicitSolver : public AbstractOdeSolver{
public:
    AbstractImplicitSolver();
    AbstractImplicitSolver(const double h, const double t0, const double t1, const double y0,
                           double (*f)(double y, double t),double (*df)(double y, double t),const unsigned int s);
    virtual ~AbstractImplicitSolver();

    void SetdRightHandSide(double (*f)(double y, double t));
    double dRightHandSide(double y, double t) const;

private:
    double (*df_rhs)(double y, double t);
};


#endif
