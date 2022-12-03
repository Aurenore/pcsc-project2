#include "AbstractOdeSolver.hpp"
#include "AdamsBashforthSolver.h"
#include <iostream>
#include <fstream>

double fRhs(double y, double t) { return 1 + t; }

int main(int argc, char **argv) {
    double h=1e-4;
    double t0=0;
    double t1=2;
    double y0=1;
    unsigned int s=1;
    AbstractOdeSolver *pSolver = new AdamsBashforthSolver(h, t0, t1, y0, fRhs, s);
    AdamsBashforthSolver solver1(h, t0, t1, y0, fRhs, s);

    std::cout << "AdamsBashforth solver has been declared." << std::endl;
    std::ofstream SolutionFile("solution_.dat");
    if (SolutionFile.is_open()) {
        solver1.SolveEquation(SolutionFile);
        SolutionFile.close();
    } else {
        std::cout << "Couldn't open solution_.dat. Aborting." << std::endl;
        return 1;
    }
    return 0;
}
