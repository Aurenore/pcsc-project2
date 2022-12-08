/*
 * AbstractOdeSolver.cpp
 *
 *  Created on: Oct 25, 2012
 *      Author: rpopescu
 */

#include "AbstractOdeSolver.hpp"
#include <cassert>
#include <iostream>

AbstractOdeSolver::AbstractOdeSolver()
/**
    * Constructor of the class, assigning the variables of the class to default values.
 */
    : stepSize(), initialTime(), finalTime(), initialValue(), f_rhs(0), s(0) {}

AbstractOdeSolver::~AbstractOdeSolver() {}

void AbstractOdeSolver::SetStepSize(const double h) {

/*! Set the step size
 * \param h: value given to the step size
*/
    assert(h>0);
    stepSize = h;
}

void AbstractOdeSolver::SetTimeInterval(const double t0, const double t1) {

/*! Set the time interval
* \param t0: initial time
*\param t1: final time
*/
    assert(t1>t0);
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

void AbstractOdeSolver::SetOrder(const unsigned int order) {
/*! Set order of the method used to solve the ODE
* \param order: value given to order
*/
    assert(order>=0);
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

double AbstractOdeSolver::GetB(const unsigned int i, const unsigned int j) const {
/*!
 * \param i: row index
 * \param j: column index
 * \return The evaluation of  b at position (i,j)
*/
    assert((i>=0) && (i<max_order) && (j>=0) && (j<max_order));
    assert(i>=j); //since the B matrix is triangular inferior
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

double AbstractOdeSolver::ProductWithB(const double *F, const int j) const {
/*! Implementation of the scalar product between vectors F and the vectors of coefficients b
* \param F: vector of size order+1 containing the evaluation of f(y,t) at different consecutive times
* \param j: parameter defining the length of F and b to consider
*\return: result of the scalar product between b and F
*/
    //Product with B : return sum_{i = 0}^{j-1} F[i]*b[j-1][i]
    double product;
    product = ScalarProduct(j, F, &b[j-1][0]);
    return product;
}


