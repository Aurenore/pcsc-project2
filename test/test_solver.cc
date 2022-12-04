#include <cmath>
#include <gtest/gtest.h>
#include "../src/AdamsBashforthSolver.h"
#include "../src/RKSolver.h"
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

TEST(AdamsBashforthSolver_test, Solver_order_2) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 2;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs2, s);
    std::fstream SolveFile;
    SolveFile.open("test_solve_s2.dat", std::ios::out);
    if (SolveFile.is_open()) {
        solver.SolveEquation(SolveFile);
        SolveFile.close();
    } else {
        std::cerr << "Couldn't open test_solve_s2.dat Aborting." << std::endl;
    }

    // check that the last line correspond between the solve data and the solution given by Euler Forward
    SolveFile.open("test_solve_s2.dat", std::ios::in);
    std::fstream SolutionFile;
    SolutionFile.open("solution_euler.dat", std::ios::in);
    while(SolveFile.is_open() && SolutionFile.is_open()){
        // store the line and previous lines of the files
        std::string solve_line;
        std::string solve_line_prev;
        std::string solution_line;
        std::string solution_line_prev;

        do{
            solve_line_prev = solve_line;
        }while(std::getline(SolveFile, solve_line));
        do{
            solution_line_prev = solution_line;
        }while(std::getline(SolutionFile, solution_line));

        //only check that the last line is similar.
        std::stringstream ss(solve_line_prev);
        double t;   ss >> t; //read 100
        double y; ss >> y;   // read 1

        std::stringstream ss_sol(solution_line_prev);
        double t_sol; ss_sol >> t_sol;
        double y_sol; ss_sol >> y_sol;

        EXPECT_DOUBLE_EQ(y, y_sol);
        EXPECT_DOUBLE_EQ(t, t_sol);

        SolveFile.close();
        SolutionFile.close();
    }
}

TEST(AdamsBashforthSolver_test, Solver_order_3) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 3;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs2, s);
    std::fstream SolveFile;
    SolveFile.open("test_solve_s3.dat", std::ios::out);
    if (SolveFile.is_open()) {
        solver.SolveEquation(SolveFile);
        SolveFile.close();
    } else {
        std::cerr << "Couldn't open test_solve_s3.dat Aborting." << std::endl;
    }

    // check that the last line correspond between the solve data and the solution given by Euler Forward
    SolveFile.open("test_solve_s3.dat", std::ios::in);
    std::fstream SolutionFile;
    SolutionFile.open("solution_euler.dat", std::ios::in);
    while(SolveFile.is_open() && SolutionFile.is_open()){
        // store the line and previous lines of the files
        std::string solve_line;
        std::string solve_line_prev;
        std::string solution_line;
        std::string solution_line_prev;

        do{
            solve_line_prev = solve_line;
        }while(std::getline(SolveFile, solve_line));
        do{
            solution_line_prev = solution_line;
        }while(std::getline(SolutionFile, solution_line));

        //only check that the last line is similar.
        std::stringstream ss(solve_line_prev);
        double t;   ss >> t; //read 100
        double y; ss >> y;   // read 1

        std::stringstream ss_sol(solution_line_prev);
        double t_sol; ss_sol >> t_sol;
        double y_sol; ss_sol >> y_sol;

        EXPECT_NEAR(y, y_sol, 1e-10);
        EXPECT_NEAR(t, t_sol, 1e-10);

        SolveFile.close();
        SolutionFile.close();
    }
}

TEST(AdamsBashforthSolver_test, Solver_order_4) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 4;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs2, s);
    std::fstream SolveFile;
    SolveFile.open("test_solve_s4.dat", std::ios::out);
    if (SolveFile.is_open()) {
        solver.SolveEquation(SolveFile);
        SolveFile.close();
    } else {
        std::cerr << "Couldn't open test_solve_s4.dat Aborting." << std::endl;
    }

    // check that the last line correspond between the solve data and the solution given by Euler Forward
    SolveFile.open("test_solve_s4.dat", std::ios::in);
    std::fstream SolutionFile;
    SolutionFile.open("solution_euler.dat", std::ios::in);
    while(SolveFile.is_open() && SolutionFile.is_open()){
        // store the line and previous lines of the files
        std::string solve_line;
        std::string solve_line_prev;
        std::string solution_line;
        std::string solution_line_prev;

        do{
            solve_line_prev = solve_line;
        }while(std::getline(SolveFile, solve_line));
        do{
            solution_line_prev = solution_line;
        }while(std::getline(SolutionFile, solution_line));

        //only check that the last line is similar.
        std::stringstream ss(solve_line_prev);
        double t;   ss >> t; //read 100
        double y; ss >> y;   // read 1

        std::stringstream ss_sol(solution_line_prev);
        double t_sol; ss_sol >> t_sol;
        double y_sol; ss_sol >> y_sol;

        EXPECT_NEAR(y, y_sol, 1e-10);
        EXPECT_NEAR(t, t_sol, 1e-10);

        SolveFile.close();
        SolutionFile.close();
    }
}

TEST(AdamsBashforthSolver_test, Solver_order_5) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 5;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs2, s);
    std::fstream SolveFile;
    SolveFile.open("test_solve_s5.dat", std::ios::out);
    if (SolveFile.is_open()) {
        solver.SolveEquation(SolveFile);
        SolveFile.close();
    } else {
        std::cerr << "Couldn't open test_solve_s5.dat Aborting." << std::endl;
    }

    // check that the last line correspond between the solve data and the solution given by Euler Forward
    SolveFile.open("test_solve_s5.dat", std::ios::in);
    std::fstream SolutionFile;
    SolutionFile.open("solution_euler.dat", std::ios::in);
    while(SolveFile.is_open() && SolutionFile.is_open()){
        // store the line and previous lines of the files
        std::string solve_line;
        std::string solve_line_prev;
        std::string solution_line;
        std::string solution_line_prev;

        do{
            solve_line_prev = solve_line;
        }while(std::getline(SolveFile, solve_line));
        do{
            solution_line_prev = solution_line;
        }while(std::getline(SolutionFile, solution_line));

        //only check that the last line is similar.
        std::stringstream ss(solve_line_prev);
        double t;   ss >> t; //read 100
        double y; ss >> y;   // read 1

        std::stringstream ss_sol(solution_line_prev);
        double t_sol; ss_sol >> t_sol;
        double y_sol; ss_sol >> y_sol;

        EXPECT_NEAR(y, y_sol, 1e-10);
        EXPECT_NEAR(t, t_sol, 1e-10);

        SolveFile.close();
        SolutionFile.close();
    }
}


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
    RKSolver solver(h, t0, t1, y0, fRhs, s);
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
    std::ofstream SolveFile("test_RK_EulerForward.dat");
    if (SolveFile.is_open()) {
        solver.SolveEquation(SolveFile);
        SolveFile.close();
    } else {
        std::cerr << "Couldn't open test_RK_EulerForward.dat Aborting." << std::endl;
    }

    // check that the lines correspond between the solve data and the solution given by Euler Forward
    std::fstream SolveFile_in;
    SolveFile_in.open("test_RK_EulerForward.dat", std::ios::in);

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