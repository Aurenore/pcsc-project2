//
// Created by anyam on 30.11.2022.
//

#include "AdamsBashforthSolver.h"
#include <cassert>
#include <iostream>
#include <cmath>


void AdamsBashforthSolver::SetB(){
    // test if sum of b is equal to 1
    b = new double [s+1];
    switch(s)
    {
        case 1:
            b[0] = 1;
            b[1] = 0;
            break;
        case 2:
            b[0] = -1/2;
            b[1] = 3/2;
            b[2] = 0;
            break;
        case 3:
            b[0] = 5/12;
            b[1] = -16/12;
            b[2] = 23/12;
            b[3] = 0;
            break;
        case 4:
            b[0] = -9/24;
            b[1] = 37/24;
            b[2] = -59/24;
            b[3] = 55/24;
            b[4] = 0;
            break;
        case 5:
            b[0] = 251/720;
            b[1] = -1274/720;
            b[2] = 2616/720;
            b[3] = -2774/720;
            b[4] = 1901/720;
            b[5] = 0;
            break;
        default:
            //compute with integrals
            break;
    }
}
double AdamsBashforthSolver::SolveEquation(std::ostream &stream) {
    double y = GetInitialValue();
    double t = GetInitialTime();
    double h = GetStepSize();
    assert(h > 1e-6);
    std::cout << "Step size: " << h << std::endl;

    int n = static_cast<int>(std::floor((GetFinalTime() - GetInitialTime()) / h));

    stream << t << " " << y << "\n";
    double temp[GetOrder() + 1];
    temp[0] = y;
    if (GetOrder() > 1) {
        for (int j = 1; j < GetOrder(); j++) {
            //WRITE HERE
            //f = ...
            //AdamsBashforthSolver solver(h, t, GetFinalTime(), y0, f, j);
            temp[j] = 0;
        }
    }

    for (int i = 1; i <= n; ++i) {
        double temp = y + h * RightHandSide(y, t);
        if (-1e-6 <= temp && temp <= 0.0) {
            y = 0.0;
        } else if (1.0 <= temp && temp <= (1.0 + 1e-6)) {
            y = 1.0;
        } else if (0.0 < temp && temp < 1.0) {
            y = temp;
        } else {
            // Freak out!
            //throw Exception("STEP", "Step size too large.");
        }
        t += h;

        stream << t << " " << y << "\n";
    }
    return y;
}