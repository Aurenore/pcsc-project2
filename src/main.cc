#include "AbstractOdeSolver.hpp"
#include "AdamsBashforthSolver.h"
#include "RKSolver.h"
#include "FileNotOpenException.hpp"
#include <iostream>

int choice;
double fRhs(double y,double t){
    if (choice==1) {
        return 1 + t;
    } else if (choice==2) {
        return -100*y;
    } else if(choice==3){
        return sin(t)*cos(t);
    }
}
double dfRhs(double y, double t) {
    if (choice == 1) {
        return 0;
    } else if (choice == 2) {
        return -100;
    } else if (choice == 3) {
        return 0;
    }
}

int main(int argc, char **argv) {
    std::cout<< "Please enter the function you want among these functions:" <<std::endl;
    std::cout <<"1: f(y,t) = 1+t" <<std::endl;
    std::cout<<"2: f(y,t) = -100*y" <<std::endl;
    std::cout<<"3 : f(y,t) = sin(t)*cos(t)" <<std::endl;
    std::cout<<"You choose function number:";
    std::cin>>choice;

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
