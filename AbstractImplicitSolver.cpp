//
// Created by anyam on 30.11.2022.
//

#include "AbstractImplicitSolver.h"
AbstractImplicitSolver::AbstractImplicitSolver(const double h, const double t0, const double t1, const double y0,
                                               double (*f)(double, double), double (*df)(double, double),const unsigned int s) :
        AbstractOdeSolver(h, t0, t1, y0, f, s){
        SetdRightHandSide(df);
 }
AbstractImplicitSolver::AbstractImplicitSolver() : AbstractOdeSolver(){}
AbstractImplicitSolver::~AbstractImplicitSolver() = default;

void AbstractImplicitSolver::SetdRightHandSide(double (*f)(double y, double t)) {
    df_rhs = f;
}

double AbstractImplicitSolver::dRightHandSide(double y, double t) const {
    return df_rhs(y, t);
}