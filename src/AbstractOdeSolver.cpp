/*
 * AbstractOdeSolver.cpp
 *
 *  Created on: Oct 25, 2012
 *      Author: rpopescu
 */

#include "AbstractOdeSolver.hpp"
#include <cassert>

AbstractOdeSolver::AbstractOdeSolver()
    : stepSize(), initialTime(), finalTime(), initialValue(), f_rhs(0), s(0) {}

AbstractOdeSolver::~AbstractOdeSolver() {}

void AbstractOdeSolver::SetStepSize(const double h) {
    assert(h>0);
    stepSize = h;
}

void AbstractOdeSolver::SetTimeInterval(const double t0, const double t1) {
    assert(t1>t0);
    initialTime = t0;
    finalTime = t1;
}

void AbstractOdeSolver::SetInitialValue(const double y0) { initialValue = y0; }

void AbstractOdeSolver::SetRightHandSide(double (*f)(double y, double t)) {
  f_rhs = f;
}

void AbstractOdeSolver::SetOrder(const unsigned int order) {
    assert(order>=0);
    s = order;
}

double AbstractOdeSolver::RightHandSide(double y, double t) const {
  return f_rhs(y, t);
}

AbstractOdeSolver::AbstractOdeSolver(const double h, const double t0, const double t1, const double y0,
                                     double (*f)(double, double), const unsigned int s) {
    SetStepSize(h);
    SetTimeInterval(t0, t1);
    SetInitialValue(y0);
    SetRightHandSide(f);
    SetOrder(s);
}

double AbstractOdeSolver::GetB(const unsigned int i, const unsigned int j) const {
    assert((i>=0) && (i<max_order) && (j>=0) && (j<max_order));
    assert(i>=j); //since the B matrix is triangular inferior
    return b[i][j];
}

double AbstractOdeSolver::ProductWithB(const double *F, const int j) const {
    double product(0);
    for(int i=0; i<j; i++){
        product += F[i]*b[j-1][i];
    }
    return product;
}
