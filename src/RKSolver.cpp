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
    SetB();
    SetC();
}

RKSolver::RKSolver(const double h, const double t0, const double t1, const double y0,
                   double (*f)(double, double), const unsigned int s) : AbstractExplicitSolver(h,t0,t1,y0,f,s) {
    SetOrder(s);
}

RKSolver::~RKSolver() = default;

void RKSolver::SetB(){
    // test if sum of b is equal to 1
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
    //test if sum of a_ij = c_i for i = 2, ..., s
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

double RKSolver::GetC(const int i, const int j) const {
    assert(i>=0 && i<max_order && i>=0);
    assert(j<=i);
    return c[i][j];
}

void RKSolver::SetA() {
    unsigned int order = GetOrder();
    try {
        if (order<1) {
            throw UnsetOrderException("When setting the coefficient As, the order needs to be set.");
        }
    } catch (UnsetOrderException &error) {
        error.PrintDebug();
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

double RKSolver::GetA(const int i, const int j) const {
    try {
        if (i<0 || i>=max_order || j<0) {
            throw OutOfRangeException("Out of range index.");
        }
    } catch (OutOfRangeException &error) {
        error.PrintDebug();
    }

    try {
        if (j>i) {
            throw OutOfRangeException("j must be smaller or equal to i.");
        }
    } catch (OutOfRangeException &error) {
        error.PrintDebug();
    }

    unsigned int order = GetOrder();
    try {
        if (order<1) {
            throw UnsetOrderException("When setting the coefficient As, the order needs to be set.");
        }
    } catch (UnsetOrderException &error) {
        error.PrintDebug();
    }

    return a[i][j];
}

void RKSolver::SetOrder(const unsigned int order) {
    try {
        if(order < 1) {
            throw SetOrderException("Order of the RK solver should be bigger or equal to 1.");
        }
    } catch (SetOrderException &error) {
        error.PrintDebug();
    }
    try {
        if (order >= max_order) {
            throw SetOrderException("Order of the RK solver should be smaller or equal to 4.");
        }
    } catch (SetOrderException &error) {
        error.PrintDebug();
    }
    s = order;
    SetB();
    SetC();
    SetA();
}

double RKSolver::ProductWithA(const double *k, const int j) const {
    // compute sum_{i=0}^{j-1} a[j][i]*k[i]
    double product;
    product = ScalarProduct(j, k, &a[j][0]);
    return product;
}


void RKSolver::SolveEquation(std::ostream &stream) {
    double y = GetInitialValue();
    double t = GetInitialTime();
    double h = GetStepSize();
    unsigned int order = GetOrder();
    assert(h > 1e-6);
    //std::cout << "RK solver : Step size: " << h << std::endl;

    int n = static_cast<int>(std::floor((GetFinalTime() - GetInitialTime()) / h));

    stream << t << " " << y << "\n";
    double temp; // y_n
    double k[order]; // k_0, k_1, ..., k_{order-1}
    temp = y;
    double product(0);
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













