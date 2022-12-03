#include <cmath>
#include <gtest/gtest.h>
#include "../src/AdamsBashforthSolver.h"
#include <fstream>
#include <string>

TEST(AdamsBashforthSolver_test, GetFinalTime) {
    AdamsBashforthSolver solver;
    double t0(2);
    double t1(4);
    solver.SetTimeInterval(t0,t1);
    EXPECT_DOUBLE_EQ(t1, solver.GetFinalTime());
}

TEST(AdamsBashforthSolver_test, GetInitialTime) {
    AdamsBashforthSolver solver;
    double t0(2);
    double t1(4);
    solver.SetTimeInterval(t0,t1);
    EXPECT_DOUBLE_EQ(t0, solver.GetInitialTime());
}

TEST(AdamsBashforthSolver_test, GetStepSize) {
    AdamsBashforthSolver solver;
    double h=1e-3;
    solver.SetStepSize(h);
    EXPECT_DOUBLE_EQ(h, solver.GetStepSize());
}

TEST(AdamsBashforthSolver_test, GetInitialValue) {
    AdamsBashforthSolver solver;
    double y0 = 2.8;
    solver.SetInitialValue(y0);
    EXPECT_DOUBLE_EQ(y0, solver.GetInitialValue());
}

TEST(AdamsBashforthSolver_test, SetOrder) {
    AdamsBashforthSolver solver;
    unsigned int s=1;
    solver.SetOrder(s);
    EXPECT_EQ(s, solver.GetOrder());
}

double fRhs(double y, double t) { return 1 + t; }
TEST(AdamsBashforthSolver_test, second_Constructor) {
    double h=1e-4;
    double t0=0;
    double t1=2;
    double y0=1;
    unsigned int s=1;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs, s);
    EXPECT_DOUBLE_EQ(t0, solver.GetInitialTime());
}

TEST(AdamsBashforthSolver_test, B_sum_order1) {
    // check that the coefficient of b sum to 1 for each order
    AdamsBashforthSolver solver;
    for(int order=1; order<=max_order; order++){
        double sum(0);
        for(int i=0; i<order; i++){
            sum += solver.GetB(order-1,i);
        }
        EXPECT_DOUBLE_EQ(1., sum);
    }
}
double fRhs2(double y, double t) { return -100*y; }
TEST(AdamsBashforthSolver_test, EulerForward) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 1;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs2, s);
    std::ofstream SolveFile("test_solve.dat");
    if (SolveFile.is_open()) {
        solver.SolveEquation(SolveFile);
        SolveFile.close();
    } else {
        std::cerr << "Couldn't open test_solve.dat Aborting." << std::endl;
    }

    // check that the lines correspond between the solve data and the solution given by Euler Forward
    std::fstream SolveFile_in;
    SolveFile_in.open("test_solve.dat", std::ios::in);

    std::fstream SolutionFile;
    SolutionFile.open("solution_euler.dat", std::ios::in);

    while(SolveFile_in.is_open() && SolutionFile.is_open()){
        std::string solve_line;
        std::string solution_line;
        while(std::getline(SolveFile_in, solve_line) && std::getline(SolutionFile, solution_line)){
            EXPECT_TRUE(solve_line == solution_line);
        }
        SolveFile_in.close();
        SolutionFile.close();
    }
}