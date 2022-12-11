/*
 * AbstractOdeSolver.cpp
 *
 *  Created on: Oct 25, 2012
 *      Author: rpopescu
 */

#include "AbstractOdeSolver.hpp"
#include "OutOfRangeException.h"
#include "UncoherentValueException.h"
#include "SetOrderException.h"
#include <iostream>

AbstractOdeSolver::AbstractOdeSolver()
/**
    * Constructor of the class, assigning the variables of the class to default values.
    * A solver find a solution \f$ y \f$ at a final time \f$t_1\f$ of the initial value problem
     \f$ \frac{dy}{dt} f(t,y), \quad y(t_0) = y_0, \f$
     given a step size \f$ h>0 \f$ and an order \f$ s \geq 0 \f$.
 */
    : stepSize(), initialTime(), finalTime(), initialValue(), f_rhs(0), s(0) {}

AbstractOdeSolver::~AbstractOdeSolver() {}

void AbstractOdeSolver::SetStepSize(double h) {

/*! Set the step size
 * \param h: value given to the step size
*/
    try {
        if (h<0) {
            throw UncoherentValueException("The step size must be positive.");
        }
    } catch (UncoherentValueException &error) {
        error.PrintDebug();
        std::cout << "The step size is to |h|." << std::endl;
        h = -h;
    }
    try {
        if (h<1e-6) {
            throw UncoherentValueException("The step size is too small.");
        }
    } catch (UncoherentValueException &error) {
        error.PrintDebug();
        std::cout << "The step size is to 1e-5" << std::endl;
        h = 1e-5;
    }
    stepSize = h;
}

void AbstractOdeSolver::SetTimeInterval(double t0, double t1) {

/*! Set the time interval
* \param t0: initial time
*\param t1: final time
*/
    try {
        if (t1<t0) {
            throw UncoherentValueException("Final time cannot be smaller than initial time.");
        }
    } catch (UncoherentValueException &error) {
        error.PrintDebug();
        std::cout << "t1 and t0 are switched." << std::endl;
        double temp(t0);
        t0 = t1;
        t1 = temp;
    }
    initialTime = t0;
    finalTime = t1;
}

void AbstractOdeSolver::SetInitialValue(const double y0) {

/*! Set the initial value
* \param y0: initial value
* */
        initialValue = y0;
    }

void AbstractOdeSolver::SetRightHandSide(double (*f)(double y, double t)) {
/*!
* Set f(y,t): f_rhs with an external function f
* \param t: time in seconds
* \param y: numerical solution at a certain time t
*
*/
  f_rhs = f;
}

void AbstractOdeSolver::SetOrder(unsigned int order) {
/*! Set order of the method used to solve the ODE
* \param order: value given to order
*/
    try {
        if (order > max_order) {
            throw SetOrderException("Order must be smaller than the maximum order " + std::to_string(max_order));
        }
    } catch (SetOrderException &error) {
        error.PrintDebug();
        std::cout << "The order is set to the maximum order " + std::to_string(max_order) << std::endl;
        order = max_order;
    }
    s = order;
}

double AbstractOdeSolver::RightHandSide(double y, double t) const {
/*!
  * \param t: time in seconds
  * \param y: numerical solution at a certain time t
  * \return The evaluation of f_rhs(y,t)
*/
  return f_rhs(y, t);
}

AbstractOdeSolver::AbstractOdeSolver(const double h, const double t0, const double t1, const double y0,
                                     double (*f)(double, double), const unsigned int s) {
        /**
           * Constructor assigning the variables of the class to specific values.
        */
    SetStepSize(h);
    SetTimeInterval(t0, t1);
    SetInitialValue(y0);
    SetRightHandSide(f);
    SetOrder(s);
}

double AbstractOdeSolver::GetB(unsigned int i, unsigned int j) const {
/*!
 * \param i: row index
 * \param j: column index
 * \return The evaluation of  b at position (i,j)
*/
    try {
        if (i>=max_order) {
            throw OutOfRangeException("Out of range index. i cannot be bigger than max_order");
        }
    } catch (OutOfRangeException &error) {
        error.PrintDebug();
        std::cout << "i is set to " << std::to_string(max_order) << "-1" << std::endl;
        i = max_order-1;
    }
    try {
        if (j>max_order) {
            throw OutOfRangeException("Out of range index. i cannot be strictly bigger than max_order");
        }
    } catch (OutOfRangeException &error) {
        error.PrintDebug();
        std::cout << "j is set to " << std::to_string(max_order) << std::endl;
        j = max_order;
    }
    return b[i][j];
}

double AbstractOdeSolver::ScalarProduct(const int size, const double *a, const double *b) const {
/*! Implementation of the scalar product between vectors a and b
* \param size: length of a and b
* \param a: first vector
* \param b: second vector
* \return: result of the scalar product between two vectors
*/
    double product(0.);
    for(int i=0; i<size; i++){
        product += a[i]*b[i];
    }
    return product;
}

double AbstractOdeSolver::ProductWithB(const double *F, int j) const {
/*! Implementation of the scalar product between vectors F and the jth row of B, i.e.
 *  \f$ \sum_{i = 0}^{j-1} F[i]*b[j-1][i] \f$
* \param F: vector of size order+1 containing the evaluation of f(y,t) at different consecutive times
* \param j: parameter defining the length of F and b to consider
*\return: result of the scalar product between F and the jth row of b
*/
    try {
        if (j>max_order) {
            throw OutOfRangeException("j must be smaller than max_order.");
        }
    } catch (OutOfRangeException &error) {
        error.PrintDebug();
        std::cout << "j is set to " << std::to_string(max_order) << std::endl;
        j = max_order;
    }
    try {
        if (j<1) {
            throw OutOfRangeException("j must be strictly positive.");
        }
    } catch (OutOfRangeException &error) {
        error.PrintDebug();
        std::cout << "j is set 1. " << std::endl;
        j = 1;
    }
    double product;
    product = ScalarProduct(j, F, &b[j-1][0]);
    return product;
}


