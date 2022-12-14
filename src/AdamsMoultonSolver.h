#ifndef ADAMSMOULTONSOLVERHEADERDEF
#define ADAMSMOULTONSOLVERHEADERDEF

#include "AbstractImplicitSolver.h"


/**
 * /** Daughter of Abstract Implicit Solver class.
 * The Adams Moulton solver solves the initial value problem
     \f$ \frac{dy}{dt} f(t,y), \quad y(t_0) = y_0 \f$
   It is an ensemble of implicit methods of different orders between 0 and 4 included.
 */

class AdamsMoultonSolver : public AbstractImplicitSolver {
public:
    AdamsMoultonSolver();
    AdamsMoultonSolver(const double h, const double t0, const double t1, const double y0,
                         double (*f)(double y, double t),double (*df)(double y, double t), const unsigned int s);
    ~AdamsMoultonSolver() override;
    void SetOrder(const unsigned int order) override;
    void SolveEquation(std::ostream &stream) override;


protected:
    void SetB() override;
};


#endif
