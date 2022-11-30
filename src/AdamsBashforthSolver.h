//
// Created by anyam on 30.11.2022.
//

#ifndef PCSC_PROJECT_ADAMSBASHFORTHSOLVER_H
#define PCSC_PROJECT_ADAMSBASHFORTHSOLVER_H

#include "AbstractExplicitSolver.h"

class AdamsBashforthSolver : public AbstractExplicitSolver {
public:
    AdamsBashforthSolver();
    virtual ~AdamsBashforthSolver();

    virtual void SolveEquation(std::ostream &stream);
};


#endif //PCSC_PROJECT_ADAMSBASHFORTHSOLVER_H
