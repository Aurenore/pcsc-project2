
#include "AdamsMoultonSolver.h"
#include "SetOrderException.h"
#include "Exception.hpp"

#include <cassert>
#include <iostream>
#include <cmath>
AdamsMoultonSolver::AdamsMoultonSolver() : AbstractImplicitSolver() {
    /**
    Constructor of an AdamsMoultonSolver instance.
    */
    SetB();
}

AdamsMoultonSolver::AdamsMoultonSolver(const double h, const double t0, const double t1, const double y0,
                                       double (*f)(double, double), double (*df)(double, double),const unsigned int s) :AbstractImplicitSolver(h, t0,t1,y0, f,df,s) {
    /**
    Constructor of an AdamsMoulton instance where each parameter are defined from outside the class.
    */

    SetB();
}
AdamsMoultonSolver::~AdamsMoultonSolver() =default;

void AdamsMoultonSolver::SetOrder(unsigned int order){

    try {
        if (order > max_order-1) {
            throw SetOrderException("Order must be strictly smaller than " + std::to_string(max_order));
        }
    } catch (SetOrderException &error) {
        error.PrintDebug();
        std::cout << "The order is set to the maximum order: " << max_order-1 << std::endl;
        order = max_order-1;
    }
    AbstractOdeSolver::SetOrder(order);
    SetB();
}

void AdamsMoultonSolver::SetB(){
    // test if sum of b is equal to 1
    //b=  std::fill(b[0] + 0, b[max_order] + max_order, 0);
    /**
   * Set the matrix B of coefficients which define the equations to solve for each order.
     B is composed of 5 rows and 6 columns, the first row corresponding the coefficients included in the equation
     for order 0 and the last row for order 4.
   *
   */
    b[0][1] = 0;
    b[0][1]=1;

    b[1][1]=1./2;
    b[1][2]=1./2;

    b[2][1] = -1./12;
    b[2][2]=8./12;
    b[2][3]=5./12;

    b[3][1] = 1./24;
    b[3][2]=-5./24;
    b[3][3]= 19./24;
    b[3][4]= 9./24;

    b[4][1] = -19./720;
    b[4][2]= 106./720;
    b[4][3]= -264./720;
    b[4][4]= 646./720;
    b[4][5] = 251./720;
}

template <class Function, class FunctionDerivative>
double Newton (double y_prev,Function F, FunctionDerivative dF, double const epsilon=1e-6, int const max_iter=1000){
    /*!
     * Finds a zero of the differentiable function F using the Newton method and returns a double corresponding
       to the final approximations of the zero
     * \param y_prev: initial guess
     * \param F: function whose zero is sought
     * \param dF: derivative of F with respect to y
     * \param epsilon: tolerance on error allowed
     * \param max_iter: maximum number of operations
     *
     */
    double x_next = y_prev;
    double x_prev;
    int num_iter = 0;
    do {
        x_prev = x_next;
        x_next = x_prev - (F(x_prev)/dF(x_prev));
        ++num_iter;
    } while ((std::abs(x_next - x_prev) > epsilon) && (num_iter < max_iter));

    try {
        if ((num_iter == max_iter) && (std::abs(x_next - x_prev) > epsilon)) {
            throw Exception("MAX_IT", "Max number of iterations reached without convergence");
        }
    } catch (Exception &error) {
        error.PrintDebug();
    }

    return x_next;
}
void AdamsMoultonSolver::SolveEquation(std::ostream &stream) {
    /*!
   * Adams Moulton methods for the scalar ODE in the form y'(t)=f(y,t).
   * The Newton method is used to solve the nonlinear equation at each time t.

   * \param stream: name of the file on which write the numerical solution at each time t
   */
    double y = GetInitialValue();
    double t = GetInitialTime();
    double h = GetStepSize();
    int order = GetOrder();
    assert(h > 1e-6);

    int n = static_cast<int>(std::floor((GetFinalTime() - GetInitialTime()) / h));
    double temp[order+1];
    double F[order+1];

    temp[0] = y;
    F[0] = RightHandSide(y, t);

    stream << t << " " << y << "\n";

    if (order>0){
        for (int j = 1; j < order+1; j++) {
            t+=h;
            double product = h*ProductWithB(F,j);
            double c = product + temp[j-1];

            auto Fu = [&](double x) {
                return x - c - b[j-1][j] * h * RightHandSide(x, t);
            };

            auto dFu = [&](double x) {
                return 1 - b[j-1][j] * h * dRightHandSide(x, t);
            };
            temp[j] = Newton(temp[j-1],Fu,dFu);

            F[j] = RightHandSide(temp[j], t);

            stream << t << " " << temp[j] << "\n";
        }
    }


    for (int j = order+1; j <= n; ++j) {
        t+=h;
        double product = h*ProductWithB(F,order+1);
        double c = product + temp[order];

        auto Fu = [&](double x) {
            return x - c - b[order][order+1] * h * RightHandSide(x, t);
        };
        auto dFu = [&](double x) {
            return 1 - b[order][order+1] * h * dRightHandSide(x, t);
        };

        y = Newton(temp[order],Fu, dFu, 1e-6, 1000);
        for(int k=0; k<order; k++){
            temp[k] = temp[k+1];
            F[k] = F[k+1];
        }
        temp[order] = y;
        F[order] = RightHandSide(temp[order], t);
        stream << t << " " << temp[order] << "\n";
    }

}