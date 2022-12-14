//
// Created by anyam on 30.11.2022.
//

#include "AdamsBashforthSolver.h"
#include "FileNotOpenException.hpp"
#include "SetOrderException.h"
#include <cassert>
#include <iostream>
#include <cmath>

AdamsBashforthSolver::AdamsBashforthSolver() : AbstractExplicitSolver() {
    /**
    Constructor of an AdamsBashforthSolver instance.
    */
    AdamsBashforthSolver::SetOrder(1);
}

AdamsBashforthSolver::AdamsBashforthSolver(const double h, const double t0, const double t1, const double y0,
                                           double (*f)(double, double), const unsigned int s) : AbstractExplicitSolver
                                           (h,t0,t1,y0,f,s) {
    /**
    Constructor of an AdamsBashforthSolver instance where each parameter are defined from outside the class by the user.
    */
    AdamsBashforthSolver::SetOrder(s);
}

void AdamsBashforthSolver::SetOrder(unsigned int order){
    try {
        if(order < 1) {
            throw SetOrderException("Order of the Adamsbashforth solver should be bigger or equal to 1.");
        }
    } catch (SetOrderException &error) {
        error.PrintDebug();
        std::cout << "The order is set to 1. " << std::endl;
        order = 1;
    }
    AbstractOdeSolver::SetOrder(order);
    SetB();
}

AdamsBashforthSolver::~AdamsBashforthSolver() = default;

void AdamsBashforthSolver::SetB(){
    /**
    * Set the matrix B of coefficients which define the equations to solve for each order.
    *B is composed of 5 rows and 6 columns, the first row corresponding to the coefficients included in the equation
    *for order 1 and the last row for order 5.
     * Note that each row sums to 1.
   */
    // s = 1:
    b[0][0] = 1.;
    // s = 2:
    b[1][0] = -1./2;
    b[1][1] = 3./2;
    // s = 3:
    b[2][0] = 5./12;
    b[2][1] = -16./12;
    b[2][2] = 23./12;
    // s = 4:
    b[3][0] = -9./24;
    b[3][1] = 37./24;
    b[3][2] = -59./24;
    b[3][3] = 55./24;
    // s = 5:
    b[4][0] = 251./720;
    b[4][1] = -1274./720;
    b[4][2] = 2616./720;
    b[4][3] = -2774./720;
    b[4][4] = 1901./720;
}

void AdamsBashforthSolver::SolveEquation(std::ostream &stream) {
/*!
   \brief Implementation of the Adams Bashforth methods to solve scalar ODE in the form y'(t)=f(y,t).
   * \param stream: name of the file on which to write the numerical solution at each time t
*/
    double y = GetInitialValue();
    double t = GetInitialTime();
    double h = GetStepSize();
    unsigned int order = GetOrder();
    assert(h > 1e-6);

    int n = static_cast<int>(std::floor((GetFinalTime() - GetInitialTime()) / h));
    stream << t << " " << y << "\n";
    double temp[order+1];
    double F[order+1];
    temp[0] = y;
    F[0] = RightHandSide(y, t);
    // if the order is bigger than one, we need to compute the first y_i with AdamsBashforth with smaller degrees.
    if (order > 1) {
        for (int j = 1; j < order+1; j++) {
            double product = ProductWithB(F, j);
            temp[j] = temp[j-1] + h*product;
            t += h;
            F[j] = RightHandSide(temp[j], t);
            stream << t << " " << temp[j] << "\n";
        }
    }

    for (int i = order; i < n; ++i) {
        double product = ProductWithB(F, order);
        y = temp[order-1] + h*product;
        t += h;
        double new_F = RightHandSide(y, t);

        //store the new temporary values in temp and F:
        temp[order] = y;
        F[order] = new_F;
        for(int j=0; j<order; j++){
            temp[j] = temp[j+1];
            F[j] = F[j+1];
        }

        //store the values in the outstream
        stream << t << " " << y << "\n";
    }
}





