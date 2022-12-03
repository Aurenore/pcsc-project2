/*
 * AbstractOdeSolver.cpp
 *
 *  Created on: Oct 25, 2012
 *      Author: rpopescu
 */

#include "AbstractOdeSolver.hpp"
#include <iostream>
#include <cassert>

AbstractOdeSolver::AbstractOdeSolver()
    : stepSize(), initialTime(), finalTime(), initialValue(), f_rhs(0), s(0) {
    //this->SetB();
}

AbstractOdeSolver::~AbstractOdeSolver() {}

void AbstractOdeSolver::SetStepSize(const double h) { stepSize = h; }

void AbstractOdeSolver::SetTimeInterval(const double t0, const double t1) {
  initialTime = t0;
  finalTime = t1;
}

void AbstractOdeSolver::SetInitialValue(const double y0) { initialValue = y0; }

void AbstractOdeSolver::SetRightHandSide(double (*f)(double y, double t)) {
  f_rhs = f;
}

void AbstractOdeSolver::SetOrder(const unsigned int order) {
    s = order;
    // PB ICI : VIRTUAL METHOD CALLED
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