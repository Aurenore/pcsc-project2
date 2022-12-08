#include <cmath>
#include <gtest/gtest.h>
#include "../src/AbstractOdeSolver.hpp"
#include "../src/AdamsMoultonSolver.h"

#include <fstream>
#include <string>
#include <cmath>
#include<iostream>

const double TOL = 0.001;

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
double dfRhs1(double y, double t) { return 0; }
double sol1(double t) { return 0.5*pow(t, 2) + t; }
double fRhs2(double y, double t) { return -100*y; }
double dfRhs2(double y, double t) { return -100; }
double sol2(double t) { return exp(-100*t); }
double fRhs3(double y, double t) { return sin(t)*cos(t); }
double dfRhs3(double y, double t) { return 0; }
double sol3(double t) { return 0.5*pow(sin(t), 2); }

// TESTS:
TEST(AdamsMoultonSolver_test, GetFinalTime) {
    AdamsMoultonSolver solver;
    double t0(2);
    double t1(4);
    solver.SetTimeInterval(t0,t1);
    EXPECT_DOUBLE_EQ(t1, solver.GetFinalTime());
}

TEST(AdamsMoultonSolver_test, GetInitialTime) {
    AdamsMoultonSolver solver;
    double t0(2);
    double t1(4);
    solver.SetTimeInterval(t0,t1);
    EXPECT_DOUBLE_EQ(t0, solver.GetInitialTime());
}

TEST(AdamsMoultonSolver_test, GetStepSize) {
    AdamsMoultonSolver solver;
    double h=1e-3;
    solver.SetStepSize(h);
    EXPECT_DOUBLE_EQ(h, solver.GetStepSize());
}

TEST(AdamsMoultonSolver_test, GetInitialValue) {
    AdamsMoultonSolver solver;
    double y0 = 2.8;
    solver.SetInitialValue(y0);
    EXPECT_DOUBLE_EQ(y0, solver.GetInitialValue());
}

TEST(AdamsMoultonSolver_test, SetOrder) {
    AdamsMoultonSolver solver;
    unsigned int s=1;
    solver.SetOrder(s);
    EXPECT_EQ(s, solver.GetOrder());
}

TEST(AdamsMoultonSolver_test, second_Constructor) {
    double h=1e-4;
    double t0=0;
    double t1=2;
    double y0=1;
    unsigned int s=1;
    AdamsMoultonSolver solver(h, t0, t1, y0, fRhs1,dfRhs1, s);
    EXPECT_DOUBLE_EQ(t0, solver.GetInitialTime());
}

TEST(AdamsMoultonSolver_test, B_sum_order1) {
    // check that the coefficient of b sum to 1 for each order
    AdamsMoultonSolver solver;
    for(int order=1; order<=max_order; order++){
        double sum(0);
        for(int i=0; i<order+1; i++){

            sum += solver.GetB(order-1,i);

        }
        EXPECT_DOUBLE_EQ(1., sum);
    }
}

TEST(AdamsMoultonSolver_test, ScalarProduct) {
    AdamsMoultonSolver solver;
    int order = 6;
    double ones[order];
    for(int i=0; i<order; i++){
        ones[i]=1;
    }
    double sum = solver.ScalarProduct(order, &ones[0], &ones[0]);
    EXPECT_DOUBLE_EQ(order, sum);
}
// NOt compatible - would need to change the for loop in the product with B
//TEST(AdamsMoultonSolver_test, ProductWithB) {
    //AdamsMoultonSolver solver;
    //for(int order=1; order<=max_order; order++){
        //double ones[order+1];
        //std::cout<<order+1<<std::endl;
        //for(int i=0; i<order+1; i++){
            //ones[i]=1;
        //}
        //double sum = solver.ProductWithB(ones, order+1);
        //EXPECT_DOUBLE_EQ(1., sum);
    //}
//}

TEST(AdamsMoultonSolver_test, EulerForward_fRhs1) {
    double h = 0.0001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.;
    unsigned int s = 1;
    AdamsMoultonSolver solver(h, t0, t1, y0, fRhs1,dfRhs1, s);
    std::string filename_solver("test_AM_fRhs1_s1.dat");
    Test_final_results(&solver, filename_solver, sol1, 0.01);
}

TEST(AdamsMoultonSolver_test, EulerForward_fRhs2) {
    AbstractOdeSolver* pt_solver = new AdamsMoultonSolver;
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 1;
    AdamsMoultonSolver solver(h, t0, t1, y0, fRhs2,dfRhs2, s);
    std::string filename_solver("test_AM_fRhs2_s1.dat");
    std::string filename_solution("solution_euler.dat");

    //Test_results(&solver, filename_solver, filename_solution);
    Test_final_results(&solver, filename_solver, sol2, 0.01);
}

TEST(AdamsMoultonSolver_test, EulerForward_fRhs3) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.;
    unsigned int s = 1;
    AdamsMoultonSolver solver(h, t0, t1, y0, fRhs3,dfRhs3, s);
    std::string filename_solver("test_AM_fRhs3_s1.dat");
    Test_final_results(&solver, filename_solver, sol3, 0.01);
}

TEST(AdamsMoultonSolver_test, Solver_order_2_fRhs1) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.0;
    unsigned int s = 2;
    AdamsMoultonSolver solver(h, t0, t1, y0, fRhs1,dfRhs1, s);
    std::string filename_solver("test_AM_fRhs1_s2.dat");

    Test_final_results(&solver, filename_solver, sol1);
}

TEST(AdamsMoultonSolver_test, Solver_order_2_fRhs2) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 2;
    AdamsMoultonSolver solver(h, t0, t1, y0, fRhs2,dfRhs2, s);
    std::string filename_solver("test_AM_fRhs2_s2.dat");
    std::string filename_solution("solution_euler.dat");

    Test_final_results(&solver, filename_solver, filename_solution);
}

TEST(AdamsMoultonSolver_test, Solver_order_2_fRhs3) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.0;
    unsigned int s = 2;
    AdamsMoultonSolver solver(h, t0, t1, y0, fRhs3,dfRhs3, s);
    std::string filename_solver("test_AM_fRhs3_s2.dat");

    Test_final_results(&solver, filename_solver, sol3);
}

TEST(AdamsMoultonSolver_test, Solver_order_3_fRhs1) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.0;
    unsigned int s = 3;
    AdamsMoultonSolver solver(h, t0, t1, y0, fRhs1,dfRhs1, s);
    std::string filename_solver("test_AM_fRhs1_s3.dat");

    Test_final_results(&solver, filename_solver, sol1);
}

TEST(AdamsMoultonSolver_test, Solver_order_3_fRhs2) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 3;
    AdamsMoultonSolver solver(h, t0, t1, y0, fRhs2,dfRhs2, s);
    std::string filename_solver("test_AM_fRhs2_s3.dat");
    std::string filename_solution("solution_euler.dat");

    Test_final_results(&solver, filename_solver, filename_solution);
}

TEST(AdamsMoultonSolver_test, Solver_order_3_fRhs3) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.0;
    unsigned int s = 3;
    AdamsMoultonSolver solver(h, t0, t1, y0, fRhs3,dfRhs3, s);
    std::string filename_solver("test_AM_fRhs3_s3.dat");

    Test_final_results(&solver, filename_solver, sol3);
}

TEST(AdamsMoultonSolver_test, Solver_order_4_fRhs1) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.0;
    unsigned int s = 4;
    AdamsMoultonSolver solver(h, t0, t1, y0, fRhs1,dfRhs1, s);
    std::string filename_solver("test_AM_fRhs1_s4.dat");

    Test_final_results(&solver, filename_solver, sol1);
}

TEST(AdamsMoultonSolver_test, Solver_order_4_fRhs2) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 4;
    AdamsMoultonSolver solver(h, t0, t1, y0, fRhs2,dfRhs2, s);
    std::string filename_solver("test_AM_s4.dat");
    std::string filename_solution("solution_euler.dat");

    Test_final_results(&solver, filename_solver, filename_solution);
}

TEST(AdamsMoultonSolver_test, Solver_order_4_fRhs3) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.0;
    unsigned int s = 4;
    AdamsMoultonSolver solver(h, t0, t1, y0, fRhs3,dfRhs3, s);
    std::string filename_solver("test_AM_fRhs3_s4.dat");

    Test_final_results(&solver, filename_solver, sol3);
}















