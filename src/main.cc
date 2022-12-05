#include "AbstractOdeSolver.hpp"
#include "AdamsBashforthSolver.h"
#include "RKSolver.h"
#include <iostream>
#include <fstream>

double fRhs(double y, double t) { return 1 + t; }

int main(int argc, char **argv) {
    double h=1e-3;
    double t0=0;
    double t1=2;
    double y0=1;
    unsigned int s=2;
    AbstractOdeSolver *pSolver = new RKSolver(h, t0, t1, y0, fRhs, s);
    AbstractOdeSolver *pForwardEuler = new RKSolver(h, t0, t1, y0, fRhs, 1);

    std::cout << "RKsolver has been declared." << std::endl;
    std::ofstream SolutionFile("solution_.dat");
    if (SolutionFile.is_open()) {
        pSolver->SolveEquation(SolutionFile);
        SolutionFile.close();
    } else {
        std::cout << "Couldn't open solution_.dat. Aborting." << std::endl;
        return 1;
    }

    std::ofstream SolutionFile2("solution_ForwardEuler.dat");
    if (SolutionFile2.is_open()) {
        pForwardEuler->SolveEquation(SolutionFile2);
        SolutionFile2.close();
    } else {
        std::cout << "Couldn't open solution_.dat. Aborting." << std::endl;
        return 1;
    }
    return 0;
}
