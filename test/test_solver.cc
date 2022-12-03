#include <cmath>
#include <gtest/gtest.h>
#include "../src/AdamsBashforthSolver.h"

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

TEST(AdamsBashforthSolver_test, second_Constructor) {
    double h=1e-4;
    double t0=0;
    double t1=2;
    double y0=1;
    unsigned int s=1;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs, s);
}