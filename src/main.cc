#include "AbstractOdeSolver.hpp"
#include "AdamsBashforthSolver.h"
#include "RKSolver.h"
#include "FileNotOpenException.hpp"
#include <iostream>

double fRhs(double y, double t)  { return -100*y; }

int main(int argc, char **argv) {
    double h = 0.001;
    double t0 = 0.;
    double t1 = 100.;
    double y0 = 0.8;
    int order = 8;
    AbstractOdeSolver *pSolver;
    pSolver = new RKSolver;
    pSolver->SetStepSize(h);
    pSolver->SetTimeInterval(t0, t1);
    pSolver->SetInitialValue(y0);
    pSolver->SetRightHandSide(fRhs);
    pSolver->SetOrder(order);

    std::cout << "other constructor : " << std::endl;
    pSolver = new AdamsBashforthSolver(h, t0, t1, y0, fRhs, order);

    std::string filename_solver("solution_file.dat");
    std::fstream SolveFile;
    SolveFile.open(filename_solver, std::ios::out);
    try {
        if (SolveFile.is_open()) {
            pSolver->SolveEquation(SolveFile);
            SolveFile.close();
        } else {
            throw FileNotOpenException("File can't be opened.");
        }
    } catch (FileNotOpenException &error) {
        error.PrintDebug();
    }

    delete pSolver;
    return 0;
}
