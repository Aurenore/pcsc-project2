#include "AbstractOdeSolver.hpp"
#include "AdamsBashforthSolver.h"
#include <iostream>

double fRhs(double y, double t) { return 1 + t; }

int main(int argc, char **argv) {
    double h=1e-4;
    double t0=0;
    double t1=2;
    double y0=1;
    unsigned int s=1;
    //AbstractOdeSolver *pSolver = new AdamsBashforthSolver();
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs, s);
    std::cout << "AdamsBashforth solver has been declared." << std::endl;
    return 0;
}
