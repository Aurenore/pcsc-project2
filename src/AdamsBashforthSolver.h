//
// Created by anyam on 30.11.2022.
//

#ifndef PCSC_PROJECT_ADAMSBASHFORTHSOLVER_H
#define PCSC_PROJECT_ADAMSBASHFORTHSOLVER_H

#include "AbstractExplicitSolver.h"

class AdamsBashforthSolver : public AbstractExplicitSolver {
public:
    virtual double SolveEquation(std::ostream &stream);
    AdamsBashforthSolver();
    AdamsBashforthSolver(const double h, const double t0, const double t1, const double y0,
                         double (*f)(double y, double t), const unsigned int s);
    ~AdamsBashforthSolver() override;

protected:
    void SetB() override;
};


#endif //PCSC_PROJECT_ADAMSBASHFORTHSOLVER_H
