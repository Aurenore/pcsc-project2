//
// Created by anyam on 30.11.2022.
//

#ifndef PCSC_PROJECT_ADAMSBASHFORTHSOLVER_H
#define PCSC_PROJECT_ADAMSBASHFORTHSOLVER_H

#include "AbstractExplicitSolver.h"
#include <fstream>
/**
 * Daugther class of AbstractExplicitSolver, the Adams Bashforth solver is an ensemble of explicite methods of different orders.
*/
class AdamsBashforthSolver : public AbstractExplicitSolver {
public:
    virtual void SolveEquation(std::ostream &stream);
    AdamsBashforthSolver();
    AdamsBashforthSolver(const double h, const double t0, const double t1, const double y0,
                         double (*f)(double y, double t), const unsigned int s);
    ~AdamsBashforthSolver() override;
    void SetOrder(const unsigned int order) override;

protected:
    void SetB() override;
};


#endif //PCSC_PROJECT_ADAMSBASHFORTHSOLVER_H
