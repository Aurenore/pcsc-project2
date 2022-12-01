//
// Created by anyam on 30.11.2022.
//

#ifndef PCSC_PROJECT_ADAMSBASHFORTHSOLVER_H
#define PCSC_PROJECT_ADAMSBASHFORTHSOLVER_H

#include "AbstractExplicitSolver.h"

class AdamsBashforthSolver : public AbstractExplicitSolver {
public:
    virtual double SolveEquation(std::ostream &stream);

protected:
    virtual void SetB();
};


#endif //PCSC_PROJECT_ADAMSBASHFORTHSOLVER_H
