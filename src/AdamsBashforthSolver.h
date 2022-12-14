//
// Created by anyam on 30.11.2022.
//

#ifndef PCSC_PROJECT_ADAMSBASHFORTHSOLVER_H
#define PCSC_PROJECT_ADAMSBASHFORTHSOLVER_H

#include "AbstractExplicitSolver.h"
#include <fstream>
/**
 * Daugther class of AbstractExplicitSolver, the Adams-Bashforth solver is an ensemble of explicit methods of different orders.
 * It solves the initial value problem
     *\f$ \frac{dy}{dt} f(t,y), \quad y(t_0) = y_0 \f$
     * In particular, the Adams-Bashforth method of order s has the general form
     * \f$ y_{n+s} = y_{n+s-1} + h \sum_{k=1}^s \lambda_k f(t_{n+s-k}, y_{n+s-k}) \f$
     where \f$ \sum_{k=1}^s \lamda_k = 1\f$.
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
