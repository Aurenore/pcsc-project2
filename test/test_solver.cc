#include <cmath>
#include <gtest/gtest.h>
#include "../src/AbstractOdeSolver.hpp"
#include "../src/AdamsBashforthSolver.h"
#include "../src/RKSolver.h"
#include <fstream>
#include <string>
#include <cmath>

const double TOL = 1e-5;

// functions that test the results of the solver
void Test_results(AbstractOdeSolver *solver, std::string filename_solver, std::string filename_solution){
    // check that the lines correspond between the solve data and the solution
    std::fstream SolveFile;
    SolveFile.open(filename_solver, std::ios::out);
    if (SolveFile.is_open()) {
        solver->SolveEquation(SolveFile);
        SolveFile.close();
    } else {
        std::cerr << "Couldn't open " << filename_solver << " Aborting." << std::endl;
    }

    // check that the lines correspond between the solve data and the solution
    SolveFile.open(filename_solver, std::ios::in);

    std::fstream SolutionFile;
    SolutionFile.open(filename_solution, std::ios::in);
    while(SolveFile.is_open() && SolutionFile.is_open()){
        std::string solve_line;
        std::string solution_line;
        while(std::getline(SolveFile, solve_line) && std::getline(SolutionFile, solution_line)){
            EXPECT_TRUE(solve_line == solution_line);
        }
        SolveFile.close();
        SolutionFile.close();
    }
}

void Test_final_results(AbstractOdeSolver *solver, std::string filename_solver, std::string filename_solution){
    // check that the last line of result is the same as the one given in the solution file.
    std::fstream SolveFile;
    SolveFile.open(filename_solver, std::ios::out);
    if (SolveFile.is_open()) {
        solver->SolveEquation(SolveFile);
        SolveFile.close();
    } else {
        std::cerr << "Couldn't open " << filename_solver << " Aborting." << std::endl;
    }

    // check that the second to last line correspond between the solve data and the solution given by Euler Forward
    SolveFile.open(filename_solver, std::ios::in);
    std::fstream SolutionFile;
    SolutionFile.open(filename_solution, std::ios::in);
    while(SolveFile.is_open() && SolutionFile.is_open()) {
        // store the line and previous lines of the files
        std::string solve_line;
        std::string solve_line_prev;
        std::string solution_line;
        std::string solution_line_prev;

        do {
            solve_line_prev = solve_line;
        } while (std::getline(SolveFile, solve_line));
        do {
            solution_line_prev = solution_line;
        } while (std::getline(SolutionFile, solution_line));

        //only check that the last line is similar.
        std::stringstream ss(solve_line_prev);
        double t;
        ss >> t;
        double y;
        ss >> y;

        std::stringstream ss_sol(solution_line_prev);
        double t_sol;
        ss_sol >> t_sol;
        double y_sol;
        ss_sol >> y_sol;

        EXPECT_NEAR(y, y_sol, TOL);
        EXPECT_NEAR(t, t_sol, TOL);

        SolveFile.close();
        SolutionFile.close();
    }
}

void Test_final_results(AbstractOdeSolver *solver, std::string filename_solver, double (*sol)(double t), const double tol = TOL){
    // check that the last line of result is the same as the one given by the solution function.
    std::fstream SolveFile;
    SolveFile.open(filename_solver, std::ios::out);
    if (SolveFile.is_open()) {
        solver->SolveEquation(SolveFile);
        SolveFile.close();
    } else {
        std::cerr << "Couldn't open " << filename_solver << " Aborting." << std::endl;
    }

    // check that the second to last line correspond between the solve data and the solution given by Euler Forward
    SolveFile.open(filename_solver, std::ios::in);

    while(SolveFile.is_open()) {
        // store the line and previous lines of the files
        std::string solve_line;
        std::string solve_line_prev;

        do {
            solve_line_prev = solve_line;
        } while (std::getline(SolveFile, solve_line));

        //only check that the last line is similar.
        std::stringstream ss(solve_line_prev);
        double t;
        ss >> t;
        double y;
        ss >> y;

        double final_time = solver->GetFinalTime();
        double y_sol = sol(final_time);

        EXPECT_NEAR(y, y_sol, tol);
        EXPECT_NEAR(t, final_time, tol);

        SolveFile.close();
    }
}

// Right hand side and their corresponding solution we are going to test on:
double fRhs1(double y, double t) { return 1 + t; }
double sol1(double t) { return 0.5*pow(t, 2) + t; }
double fRhs2(double y, double t) { return -100*y; }
double sol2(double t) { return exp(-100*t); }
double fRhs3(double y, double t) { return sin(t)*cos(t); }
double sol3(double t) { return 0.5*pow(sin(t), 2); }

// TESTS:
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
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs1, s);
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

TEST(AdamsBashforthSolver_test, ScalarProduct) {
    AdamsBashforthSolver solver;
    int order = 6;
    double ones[order];
    for(int i=0; i<order; i++){
        ones[i]=1;
    }
    double sum = solver.ScalarProduct(order, &ones[0], &ones[0]);
    EXPECT_DOUBLE_EQ(order, sum);
}

TEST(AdamsBashforthSolver_test, ProductWithB) {
    AdamsBashforthSolver solver;
    for(int order=1; order<=max_order; order++){
        double ones[order];
        for(int i=0; i<order; i++){
            ones[i]=1;
        }
        double sum = solver.ProductWithB(ones, order);
        EXPECT_DOUBLE_EQ(1., sum);
    }
}

TEST(AdamsBashforthSolver_test, EulerForward_fRhs1) {
    double h = 0.0001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.;
    unsigned int s = 1;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs1, s);
    std::string filename_solver("test_AB_fRhs1_s1.dat");
    Test_final_results(&solver, filename_solver, sol1, 0.1);
}

TEST(AdamsBashforthSolver_test, EulerForward_fRhs2) {
    AbstractOdeSolver* pt_solver = new AdamsBashforthSolver;
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 1;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs2, s);
    std::string filename_solver("test_AB_fRhs2_s1.dat");
    std::string filename_solution("solution_euler.dat");

    Test_results(&solver, filename_solver, filename_solution);
}

TEST(AdamsBashforthSolver_test, EulerForward_fRhs3) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.;
    unsigned int s = 1;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs3, s);
    std::string filename_solver("test_AB_fRhs3_s1.dat");
    Test_final_results(&solver, filename_solver, sol3, 0.01);
}

TEST(AdamsBashforthSolver_test, Solver_order_2_fRhs1) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.0;
    unsigned int s = 2;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs1, s);
    std::string filename_solver("test_AB_fRhs1_s2.dat");

    Test_final_results(&solver, filename_solver, sol1);
}

TEST(AdamsBashforthSolver_test, Solver_order_2_fRhs2) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 2;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs2, s);
    std::string filename_solver("test_AB_fRhs2_s2.dat");
    std::string filename_solution("solution_euler.dat");

    Test_final_results(&solver, filename_solver, filename_solution);
}

TEST(AdamsBashforthSolver_test, Solver_order_2_fRhs3) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.0;
    unsigned int s = 2;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs3, s);
    std::string filename_solver("test_AB_fRhs3_s2.dat");

    Test_final_results(&solver, filename_solver, sol3);
}

TEST(AdamsBashforthSolver_test, Solver_order_3_fRhs1) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.0;
    unsigned int s = 3;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs1, s);
    std::string filename_solver("test_AB_fRhs1_s3.dat");

    Test_final_results(&solver, filename_solver, sol1);
}

TEST(AdamsBashforthSolver_test, Solver_order_3_fRhs2) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 3;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs2, s);
    std::string filename_solver("test_AB_fRhs2_s3.dat");
    std::string filename_solution("solution_euler.dat");

    Test_final_results(&solver, filename_solver, filename_solution);
}

TEST(AdamsBashforthSolver_test, Solver_order_3_fRhs3) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.0;
    unsigned int s = 3;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs3, s);
    std::string filename_solver("test_AB_fRhs3_s3.dat");

    Test_final_results(&solver, filename_solver, sol3);
}

TEST(AdamsBashforthSolver_test, Solver_order_4_fRhs1) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.0;
    unsigned int s = 4;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs1, s);
    std::string filename_solver("test_AB_fRhs1_s4.dat");

    Test_final_results(&solver, filename_solver, sol1);
}

TEST(AdamsBashforthSolver_test, Solver_order_4_fRhs2) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 4;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs2, s);
    std::string filename_solver("test_AB_s4.dat");
    std::string filename_solution("solution_euler.dat");

    Test_final_results(&solver, filename_solver, filename_solution);
}

TEST(AdamsBashforthSolver_test, Solver_order_4_fRhs3) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.0;
    unsigned int s = 4;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs3, s);
    std::string filename_solver("test_AB_fRhs3_s4.dat");

    Test_final_results(&solver, filename_solver, sol3);
}

TEST(AdamsBashforthSolver_test, Solver_order_5_fRhs1) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.0;
    unsigned int s = 5;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs1, s);
    std::string filename_solver("test_AB_fRhs1_s5.dat");

    Test_final_results(&solver, filename_solver, sol1);
}

TEST(AdamsBashforthSolver_test, Solver_order_5_fRhs2) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 5;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs2, s);
    std::string filename_solver("test_AB_s5.dat");
    std::string filename_solution("solution_euler.dat");

    Test_final_results(&solver, filename_solver, filename_solution);
}

TEST(AdamsBashforthSolver_test, Solver_order_5_fRhs3) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.0;
    unsigned int s = 5;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs3, s);
    std::string filename_solver("test_AB_fRhs3_s5.dat");

    Test_final_results(&solver, filename_solver, sol3);
}


// RUNGE KUTA SOLVER:

TEST(RKSolver_test, GetFinalTime) {
    RKSolver solver;
    double t0(2);
    double t1(4);
    solver.SetTimeInterval(t0,t1);
    EXPECT_DOUBLE_EQ(t1, solver.GetFinalTime());
}

TEST(RKSolver_test, GetInitialTime) {
    RKSolver solver;
    double t0(2);
    double t1(4);
    solver.SetTimeInterval(t0,t1);
    EXPECT_DOUBLE_EQ(t0, solver.GetInitialTime());
}

TEST(RKSolver_test, GetStepSize) {
    RKSolver solver;
    double h=1e-3;
    solver.SetStepSize(h);
    EXPECT_DOUBLE_EQ(h, solver.GetStepSize());
}

TEST(RKSolver_test, GetInitialValue) {
    AdamsBashforthSolver solver;
    double y0 = 2.8;
    solver.SetInitialValue(y0);
    EXPECT_DOUBLE_EQ(y0, solver.GetInitialValue());
}

TEST(RKSolver_test, SetOrder) {
    RKSolver solver;
    unsigned int s=1;
    solver.SetOrder(s);
    EXPECT_EQ(s, solver.GetOrder());
}

TEST(RKSolver_test, second_Constructor) {
    double h=1e-4;
    double t0=0;
    double t1=2;
    double y0=1;
    unsigned int s=1;
    RKSolver solver(h, t0, t1, y0, fRhs1, s);
    EXPECT_DOUBLE_EQ(t0, solver.GetInitialTime());
}

TEST(RKSolver_test, B_sum_order) {
    // check that the coefficient of b sum to 1 for each order
    RKSolver solver;
    for(int order=1; order<max_order; order++){
        double sum(0);
        for(int i=0; i<order; i++){
            sum += solver.GetB(order-1,i);
        }
        EXPECT_DOUBLE_EQ(1., sum);
    }
}

TEST(RKSolver_test, sum_of_A_is_C) {
    RKSolver solver;
    // loop over the orders
    for(int i=1; i<max_order; i++){
        solver.SetOrder(i);
        // loop over the rows of the A matrix
        for(int j=0; j<i; j++){
            double sum(0.);
            // sum the elements of the row
            for(int k=0; k<=j; k++){
                sum+= solver.GetA(j,k);
            }
            double c_j = solver.GetC(i-1, j);
            EXPECT_DOUBLE_EQ(sum, c_j);
        }
    }
}

TEST(RKSolver_test, EulerForward) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 1;
    RKSolver solver(h, t0, t1, y0, fRhs2, s);
    std::string filename_solver("test_RK_s1.dat");
    std::string filename_solution("solution_euler.dat");

    Test_results(&solver, filename_solver, filename_solution);
}


TEST(RKSolver_test, Solver_order_2) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 2;
    RKSolver solver(h, t0, t1, y0, fRhs2, s);
    std::string filename_solver("test_RK_s2.dat");
    std::string filename_solution("solution_euler.dat");

    Test_final_results(&solver, filename_solver, filename_solution);
}

TEST(RKSolver_test, Solver_order_3) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 3;
    RKSolver solver(h, t0, t1, y0, fRhs2, s);
    std::string filename_solver("test_RK_s3.dat");
    std::string filename_solution("solution_euler.dat");

    Test_final_results(&solver, filename_solver, filename_solution);
}

TEST(RKSolver_test, Solver_order_4) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 4;
    RKSolver solver(h, t0, t1, y0, fRhs2, s);
    std::string filename_solver("test_RK_s4.dat");
    std::string filename_solution("solution_euler.dat");

    Test_final_results(&solver, filename_solver, filename_solution);
}
