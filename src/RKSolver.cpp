//
// Created by anyam on 30.11.2022.
//

#include "RKSolver.h"
#include "UnsetOrderException.h"
#include "SetOrderException.h"
#include "OutOfRangeException.h"

#include <cassert>
#include <iostream>
#include <cmath>


RKSolver::RKSolver() : AbstractExplicitSolver() {
    /**
    Constructor of a Runge Kutta solver instance.
     The Runge-Kutta solves the initial value problem
     \f$ \frac{dy}{dt} f(t,y), \quad y(t_0) = y_0 \f$
     In particular, the Explicit Runge-Kutta methods consist of computing for \f$ n \geq 0\f$:
     \f$y_{n+1} = y_n + h \sum_{i=1}^s b_i k_i\f$
     where for \f$j=1, \dots, s\f$
     \f$ k_j = f(t_n + c_j \cdot h, y_n + h (\sum_{l=0}^{j-1} a_{j-1 \; l} k_l) ). \f$
     The coefficients \f$a_{i \; j}, b_i, c_j \f$ are given depending of the order \f$ s \f$ and the chosen method.
    */
    SetB();
    SetC();
}

RKSolver::RKSolver(const double h, const double t0, const double t1, const double y0,
                   double (*f)(double, double), const unsigned int s) : AbstractExplicitSolver(h,t0,t1,y0,f,s) {
    /**
    Constructor of a Runge Kutta solver instance, where each parameter are defined from outside the class.
     The Runge-Kutta solves the initial value problem
     \f$ \frac{dy}{dt} f(t,y), \quad y(t_0) = y_0 \f$
     In particular, the Explicit Runge-Kutta methods consist of computing for \f$ n \geq 0\f$:
     \f$y_{n+1} = y_n + h \sum_{i=1}^s b_i k_i\f$
     where for \f$j=1, \dots, s\f$
     \f$ k_j = f(t_n + c_j \cdot h, y_n + h (\sum_{l=0}^{j-1} a_{j-1 \; l} k_l) ). \f$
     The coefficients \f$a_{i \; j}, b_i, c_j \f$ are given depending of the order \f$ s \f$ and the chosen method.
    */
    SetOrder(s);
}

RKSolver::~RKSolver() = default;

void RKSolver::SetB(){
    /**
   * Set the matrix B of coefficients which define the equations to solve for each order.
     Each row corresponds to different order of the RK method.
     order = 1: Forward Euler (first order)
     order = 2: Explicit midpoint method
     order = 3: Kutta's third-order method
     order = 4: classic fourth-order method
   *
   */
    // s = 1: Forward Euler (first order)
    b[0][0] = 1.;
    // s = 2: Explicit midpoint method
    b[1][0] = 0;
    b[1][1] = 1;
    // s = 3: Kutta's third-order method
    b[2][0] = 1./6;
    b[2][1] = 2./3;
    b[2][2] = 1./6;
    // s = 4: classic fourth-order method
    b[3][0] = 1./6;
    b[3][1] = 1./3;
    b[3][2] = 1./3;
    b[3][3] = 1./6;
}

void RKSolver::SetC() {
    /**
   * Set the matrix C of coefficients which define the equations to solve for each order.
     Each row corresponds to different order of the RK method.
     order = 1: Forward Euler (first order)
     order = 2: Explicit midpoint method
     order = 3: Kutta's third-order method
     order = 4: classic fourth-order method
   *
   */
    // s = 1: Forward Euler (first order)
    c[0][0] = 0.;
    // s = 2: Explicit midpoint method
    c[1][0] = 0.;
    c[1][1] = 1./2;
    // s = 3: Kutta's third-order method
    c[2][0] = 0.;
    c[2][1] = 1./2;
    c[2][2] = 1.;
    // s = 4: classic fourth-order method
    c[3][0] = 0.;
    c[3][1] = 1./2;
    c[3][2] = 1./2;
    c[3][3] = 1.;

}

double RKSolver::GetC(int i, int j) const {
/*!
 * \param i: row index
 * \param j: column index
 * \return The evaluation of c at position (i,j)
*/
    try {
        if (i<0) {
            throw OutOfRangeException("Out of range index. i should be bigger than 0.");
        }
    } catch (OutOfRangeException &error) {
        error.PrintDebug();
        std::cout << "i is set to 0." << std::endl;
        i = 0;
    }
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
        if (j<0) {
            throw OutOfRangeException("Out of range index. j must be bigger or equal to 0.");
        }
    } catch (OutOfRangeException &error) {
        error.PrintDebug();
        std::cout << "j is set to 0." << std::endl;
        j = 0;
    }
    //since the C matrix is triangular inferior:
    try {
        if (j>i) {
            throw OutOfRangeException("j must be smaller or equal to i.");
        }
    } catch (OutOfRangeException &error) {
        error.PrintDebug();
        std::cout << "j is set equal to i. " << std::endl;
        j = i;
    }
    return c[i][j];
}

void RKSolver::SetA() {
    /**
   * Set the matrix A of coefficients which define the equations to solve for each order.
    The matrix A depends of the order of the RK method.
   *
   */
    unsigned int order = GetOrder();
    try {
        if (order<1) {
            throw UnsetOrderException("When setting the coefficient As, the order needs to be set.");
        }
    } catch (UnsetOrderException &error) {
        error.PrintDebug();
        std::cout << "The order is set to 1." << std::endl;
        SetOrder(1);
    }
    assert(order < max_order);
    switch (order) {
        case 1: // s = 1: Forward Euler (first order)
            a[0][0] = 0.;
            break;
        case 2: // s = 2: Explicit midpoint method
            a[0][0] = 0.;
            a[0][1] = 0.;
            a[1][0] = 1./2;
            a[1][1] = 0.;
            break;
        case 3: // s = 3: Kutta's third-order method
            for(int i=0; i<order; i++){
                a[0][i] = 0.;
            }
            a[1][0] = 1./2;
            a[1][1] = 0.;
            a[1][2] = 0.;
            a[2][0] = -1.;
            a[2][1] = 2.;
            a[2][2] = 0.;
            break;
        case 4: // s = 4: classic fourth-order method
            for(int i=0; i<order; i++){
                for(int j=0; j<order; j++){
                    a[j][i] = 0.;
                }
            }
            a[1][0] = 1./2;
            a[2][1] = 1./2;
            a[3][2] = 1.;
            break;
    }
}

double RKSolver::GetA(int i, int j) {
/*!
 * \param i: row index
 * \param j: column index
 * \return The evaluation of a at position (i,j)
*/
    try {
        if (i<0) {
            throw OutOfRangeException("Out of range index. i should be bigger than 0.");
        }
    } catch (OutOfRangeException &error) {
        error.PrintDebug();
        std::cout << "i is set to 0." << std::endl;
        i = 0;
    }
    try {
        if (i>=max_order) {
            throw OutOfRangeException("Out of range index. i cannot be bigger than max_order");
        }
    } catch (OutOfRangeException &error) {
        error.PrintDebug();
        i = max_order-1;
    }
    try {
        if (j<0) {
            throw OutOfRangeException("Out of range index. j must be bigger or equal to 0.");
        }
    } catch (OutOfRangeException &error) {
        error.PrintDebug();
        std::cout << "j is set to 0." << std::endl;
        j = 0;
    }
    //since the A matrix is triangular inferior:
    try {
        if (j>i) {
            throw OutOfRangeException("j must be smaller or equal to i.");
        }
    } catch (OutOfRangeException &error) {
        error.PrintDebug();
        std::cout << "j is set equal to i. " << std::endl;
        j = i;
    }
    unsigned int order = GetOrder();
    try {
        if (order<1) {
            throw UnsetOrderException("When setting the coefficient As, the order needs to be set.");
        }
    } catch (UnsetOrderException &error) {
        error.PrintDebug();
        std::cout << "the order is set to 1." << std::endl;
        SetOrder(1);
    }

    return a[i][j];
}

void RKSolver::SetOrder(unsigned int order) {
/*!
 * \param order: order that will be set for the Runge Kutta method.
*/
    try {
        if(order < 1) {
            throw SetOrderException("Order of the RK solver should be bigger or equal to 1.");
        }
    } catch (SetOrderException &error) {
        error.PrintDebug();
        std::cout << "The order is set to 1. " << std::endl;
        order = 1;
    }
    try {
        if (order >= max_order) {
            throw SetOrderException("Order of the RK solver should be smaller or equal to 4.");
        }
    } catch (SetOrderException &error) {
        error.PrintDebug();
        std::cout << "the order is set to the maximum order : 4." << std::endl;
        order = 4;
    }
    s = order;
    SetB();
    SetC();
    SetA();
}

double RKSolver::ProductWithA(const double *k, int j) const {
/*!
 * \param k: pointer to a double vector/array
 * \param j: row index of A
 * \return scalar product of k with the jth row of A, i.e. \f$\sum_{i=0}^{j-1} a[j][i]*k[i]\f$
*/
    try {
        if (j>max_order) {
            throw OutOfRangeException("j must be smaller than max_order.");
        }
    } catch (OutOfRangeException &error) {
        error.PrintDebug();
        std::cout << "j is set 4. " << std::endl;
        j = 4;
    }
    try {
        if (j<0) {
            throw OutOfRangeException("j must be positive.");
        }
    } catch (OutOfRangeException &error) {
        error.PrintDebug();
        std::cout << "j is set 0. " << std::endl;
        j = 0;
    }
    double product;
    product = ScalarProduct(j, k, &a[j][0]);
    return product;
}


void RKSolver::SolveEquation(std::ostream &stream) {
    /*!
   * Runge Kutta methods for the scalar ODE in the form y'(t)=f(y,t).

   * \param stream: name of the file on which write the numerical solution at each time t
   */

    double y = GetInitialValue();
    double t = GetInitialTime();
    double h = GetStepSize();
    unsigned int order = GetOrder();
    assert(h > 1e-6);

    int n = static_cast<int>(std::floor((GetFinalTime() - GetInitialTime()) / h));

    stream << t << " " << y << "\n";
    double temp; // y_n
    double k[order]; // k_0, k_1, ..., k_{order-1}
    temp = y;
    double product;
    double final_product;
    for (int i = 1; i <= n; ++i) {
        // compute the values k_j
        for(int j = 0; j < order; j++){
            if(j>0){
                product = ProductWithA(k, j);
            }
            else{
                product = 0;
            }
            k[j] = RightHandSide(temp + h*product, t + c[order-1][j]*h);
        }
        final_product = ProductWithB(k, order);
        y = temp + h*final_product;
        t += h;
        //store the values in the outstream
        stream << t << " " << y << "\n";
        temp = y;
    }
}













