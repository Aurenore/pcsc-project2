//
// Created by anyam on 30.11.2022.
//

#include "AbstractExplicitSolver.h"
#include "OutOfRangeException.h"
#include <iostream>

AbstractExplicitSolver::AbstractExplicitSolver(const double h, const double t0, const double t1, const double y0,
                                               double (*f)(double, double), const unsigned int s) :
                                               AbstractOdeSolver(h, t0, t1, y0, f, s) {
    /**
    * Constructor of the class, assigning the variables of the class to specific values.
 */
}
AbstractExplicitSolver::AbstractExplicitSolver() : AbstractOdeSolver(){
    /**
    * Constructor of the class, assigning the variables of the class to default values.
 */
}

double AbstractExplicitSolver::GetB(unsigned int i, unsigned int j) const {
    /*!
 * \param i: row index
 * \param j: column index
 * \return The evaluation of B at position (i,j)
*/
    //since the B matrix is triangular inferior:
    try {
        if (j>i) {
            throw OutOfRangeException("j must be smaller or equal to i.");
        }
    } catch (OutOfRangeException &error) {
        error.PrintDebug();
        std::cout << "j is set equal to i. " << std::endl;
        j = i;
    }
    return AbstractOdeSolver::GetB(i, j);
}

AbstractExplicitSolver::~AbstractExplicitSolver() = default;
