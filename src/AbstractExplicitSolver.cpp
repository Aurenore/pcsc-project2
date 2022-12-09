//
// Created by anyam on 30.11.2022.
//

#include "AbstractExplicitSolver.h"
#include "OutOfRangeException.h"

AbstractExplicitSolver::AbstractExplicitSolver(const double h, const double t0, const double t1, const double y0,
                                               double (*f)(double, double), const unsigned int s) :
                                               AbstractOdeSolver(h, t0, t1, y0, f, s) {}
AbstractExplicitSolver::AbstractExplicitSolver() : AbstractOdeSolver(){}

double AbstractExplicitSolver::GetB(const unsigned int i, const unsigned int j) const {
    try {
        if (i<0 || i>=max_order || j<0 || j>=max_order) {
            throw OutOfRangeException("Out of range index.");
        }
    } catch (OutOfRangeException &error) {
        error.PrintDebug();
    }
    //since the B matrix is triangular inferior:
    try {
        if (j>i) {
            throw OutOfRangeException("j must be smaller or equal to i.");
        }
    } catch (OutOfRangeException &error) {
        error.PrintDebug();
    }
    return AbstractOdeSolver::GetB(i, j);
}

AbstractExplicitSolver::~AbstractExplicitSolver() = default;
