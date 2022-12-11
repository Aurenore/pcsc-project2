#include "AbstractOdeSolver.hpp"
#include "AdamsBashforthSolver.h"
#include "RKSolver.h"
#include <iostream>

double fRhs(double y, double t)  { return -100*y; }

int main(int argc, char **argv) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    auto *pSolver = new RKSolver(h, t0, t1, y0, fRhs, 3);
    AbstractOdeSolver *pForwardEuler = new RKSolver(1e-8, t0, t1, y0, fRhs, 8);

    AdamsBashforthSolver *pABsolver = new AdamsBashforthSolver(-h, t1, t0, y0, fRhs, 0);

    std::cout << "instances set. " << std::endl;
    std::ofstream SolutionFile2("solution_ForwardEuler.dat");
    if (SolutionFile2.is_open()) {
        pForwardEuler->SolveEquation(SolutionFile2);
        SolutionFile2.close();
    } else {
        std::cout << "Couldn't open solution_.dat. Aborting." << std::endl;
        return 1;
    }
    delete pSolver;
    delete pForwardEuler;
    return 0;
}
