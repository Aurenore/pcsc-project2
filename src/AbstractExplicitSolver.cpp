//
// Created by anyam on 30.11.2022.
//

#include "AbstractExplicitSolver.h"

AbstractExplicitSolver::AbstractExplicitSolver(const double h, const double t0, const double t1, const double y0,
                                               double (*f)(double, double), const unsigned int s) :
                                               AbstractOdeSolver(h, t0, t1, y0, f, s) {}
AbstractExplicitSolver::AbstractExplicitSolver() : AbstractOdeSolver(){}
AbstractExplicitSolver::~AbstractExplicitSolver() = default;
