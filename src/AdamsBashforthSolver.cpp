//
// Created by anyam on 30.11.2022.
//

#include "AdamsBashforthSolver.h"
#include <cassert>
#include <iostream>
#include <cmath>

AdamsBashforthSolver::AdamsBashforthSolver() : AbstractExplicitSolver() {}

AdamsBashforthSolver::AdamsBashforthSolver(const double h, const double t0, const double t1, const double y0,
                                           double (*f)(double, double), const unsigned int s) : AbstractExplicitSolver
                                           (h, t0,t1,y0, f,s) {}

AdamsBashforthSolver::~AdamsBashforthSolver() = default;

void AdamsBashforthSolver::SetB(){
    // test if sum of b is equal to 1
    // s = 1:
    b[0][0] = 1;
    // s = 2:
    b[1][0] = -1/2;
    b[1][1] = 3/2;
    // s = 3:
    b[2][0] = 5/12;
    b[2][1] = -16/12;
    b[2][2] = 23/12;
    // s = 4:
    b[3][0] = -9/24;
    b[3][1] = 37/24;
    b[3][2] = -59/24;
    b[3][3] = 55/24;
    // s = 5:
    b[4][0] = 251/720;
    b[4][1] = -1274/720;
    b[4][2] = 2616/720;
    b[4][3] = -2774/720;
    b[4][4] = 1901/720;
}

double AdamsBashforthSolver::SolveEquation(std::ostream &stream) {
    double y = GetInitialValue();
    double t = GetInitialTime();
    double h = GetStepSize();
    unsigned int order = GetOrder();
    assert(h > 1e-6);
    std::cout << "Step size: " << h << std::endl;

    int n = static_cast<int>(std::floor((GetFinalTime() - GetInitialTime()) / h));

    stream << t << " " << y << "\n";
    double temp[order+1];
    double F[order+1];
    temp[0] = y;
    F[0] = RightHandSide(y, t);
    if (order > 1) {
        for (int j = 1; j < order+1; j++) {
            double product(0);
            for(int i = 0; i<j; i++){
                product += F[i]*b[j-1][i];
            }
            temp[j] = temp[j-1] + h*product;
            t += h;
            F[j] = RightHandSide(temp[j], t);
        }
    }

    for (int i = order+1; i <= n; ++i) {
        double product(0);
        for(int j = 0; j<order; j++){ //ajouter order+1 pour implicite
            product += F[j]*b[order-1][j];
        }
        double y = temp[order-1] + h*product;
        t += h;
        double new_F = RightHandSide(y, t);

        //store the new temporary values in temp and F:
        for(int j=0; j<order; j++){
            temp[j] = temp[j+1];
            F[j] = F[j+1];
        }
        temp[order] = y;
        F[order] = new_F;

        //store the values in the outstream
        stream << t << " " << y << "\n";
    }
    //return the final solution
    return y;
}



