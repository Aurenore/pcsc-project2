//
// Created by anyam on 30.11.2022.
//

#ifndef ADAMSMOULTONSOLVERHEADERDEF
#define ADAMSMOULTONSOLVERHEADERDEF

#include "AbstractImplicitSolver.h"


/**
 * Daugther class of AbstractImplicitSolver, the Adams Moulton solver is an ensemble of implicite methods of different orders.
 */
class AdamsMoultonSolver : public AbstractImplicitSolver {
public:
    AdamsMoultonSolver();
    AdamsMoultonSolver(const double h, const double t0, const double t1, const double y0,
                         double (*f)(double y, double t),double (*df)(double y, double t), const unsigned int s);
    ~AdamsMoultonSolver() override;
    void SolveEquation(std::ostream &stream) override;


protected:
    void SetB() override;
};


#endif