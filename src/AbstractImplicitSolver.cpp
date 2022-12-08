//
// Created by anyam on 30.11.2022.
//

#include "AbstractImplicitSolver.h"
AbstractImplicitSolver::AbstractImplicitSolver(const double h, const double t0, const double t1, const double y0,
                                               double (*f)(double, double), double (*df)(double, double),const unsigned int s) :AbstractOdeSolver(h, t0, t1, y0, f, s){
    /**
    Constructor for an Implicit class instance. This constructor is used in the constructor of the daughter class AdamsMpultonSOlver
    */
    SetdRightHandSide(df);
 }
AbstractImplicitSolver::AbstractImplicitSolver() : AbstractOdeSolver(){}
AbstractImplicitSolver::~AbstractImplicitSolver() = default;

void AbstractImplicitSolver::SetdRightHandSide(double (*f)(double y, double t)) {
    /*!
     * Set the derivative of f(y,t) with respect to y: df_rhs with an external function f
     * \param f: function handle for df(y,t)
     * \param t: time in seconds
     * \param y: numerical solution at a certain time t
     *
     */
    df_rhs = f;
}

double AbstractImplicitSolver::dRightHandSide(double y, double t) const {

    /*!
     * \param t: time in seconds
     * \param y: numerical solution at a certain time t
     * \return evaluation of the derivative of f(y,t) with respect to y
     */

    return df_rhs(y, t);
}