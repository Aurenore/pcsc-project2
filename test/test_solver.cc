#include <cmath>
#include <string>
#include <gtest/gtest.h>
#include "../src/AbstractOdeSolver.hpp"
#include "../src/AbstractExplicitSolver.h"
#include "../src/AbstractImplicitSolver.h"
#include "../src/AdamsMoultonSolver.h"
#include "../src/AdamsBashforthSolver.h"
#include "../src/RKSolver.h"
#include "../src/FileNotOpenException.hpp"

const double TOL = 1e-5;

// Right hand side, their corresponding derative and solution we are going to test on:
double fRhs1(double y, double t) { return 1 + t; }
double dfRhs1(double y, double t) { return 0; }
double sol1(double t) { return 0.5*pow(t, 2) + t; }
double fRhs2(double y, double t) { return -100*y; }
double dfRhs2(double y, double t) { return -100; }
double sol2(double t) { return exp(-100*t); }
double fRhs3(double y, double t) { return sin(t)*cos(t); }
double dfRhs3(double y, double t) { return 0; }
double sol3(double t) { return 0.5*pow(sin(t), 2); }

// functions that test the results of the solver
void Test_results(AbstractOdeSolver *solver, std::string filename_solver, std::string filename_solution){
    // check that the lines correspond between the solve data and the solution
    std::fstream SolveFile;
    SolveFile.open(filename_solver, std::ios::out);
    if (SolveFile.is_open()) {
        solver->SolveEquation(SolveFile);
        SolveFile.close();
    } else {
        throw FileNotOpenException("File can't be opened.");
    }

    // check that the lines correspond between the solve data and the solution
    SolveFile.open(filename_solver, std::ios::in);
    std::fstream SolutionFile;
    SolutionFile.open(filename_solution, std::ios::in);
    if(!(SolveFile.is_open() && SolutionFile.is_open())){
        throw FileNotOpenException("One of the 2 files can't be opened.");
    }
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

void Test_final_results(AbstractOdeSolver *solver, std::string filename_solver, double (*sol)(double t), const double tol = TOL){
    // check that the last line of result is the same as the one given by the solution function.
    std::fstream SolveFile;
    SolveFile.open(filename_solver, std::ios::out);
    if (SolveFile.is_open()) {
        solver->SolveEquation(SolveFile);
        SolveFile.close();
    } else {
        throw FileNotOpenException("File can't be opened.");
    }

    // check that the second to last line correspond between the solve data and the solution given by Euler Forward
    SolveFile.open(filename_solver, std::ios::in);
    if (!SolveFile.is_open()) {
        throw FileNotOpenException("File can't be opened.");
    }

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

void Test_function(AbstractOdeSolver *solver, std::string filename_solver, double (*fRhs)(double y, double t),
                   double (*sol)(double t), const double tol = TOL){
    solver->SetRightHandSide(fRhs);
    Test_final_results(solver, filename_solver, sol, tol);
}

void Test_orders(AbstractExplicitSolver *solver, int order_min, int order_max, std::string prefix_filename_solver,
                 double tol=TOL){
    for(int order=order_min; order<=order_max; order++){
        solver->SetOrder(order);
        std::string filename_solver = prefix_filename_solver + "order" + std::to_string(order);
        solver->SetInitialValue(0.);
        Test_function(solver, filename_solver + "_fRhs1", fRhs1, sol1, tol);
        solver->SetInitialValue(0.8);
        Test_function(solver, filename_solver + "_fRhs2", fRhs2, sol2, tol);
        solver->SetInitialValue(0.);
        Test_function(solver, filename_solver + "_fRhs3", fRhs3, sol3, tol);
    }
}

void Test_orders(AbstractImplicitSolver *solver, int order_min, int order_max, std::string prefix_filename_solver,
                 double tol=TOL){
    for(int order=order_min; order<=order_max; order++){
        solver->SetOrder(order);
        std::string filename_solver = prefix_filename_solver + "order" + std::to_string(order);
        solver->SetInitialValue(0.);
        solver->SetdRightHandSide(dfRhs1);
        Test_function(solver, filename_solver + "_fRhs1", fRhs1, sol1, tol);
        solver->SetInitialValue(0.8);
        solver->SetdRightHandSide(dfRhs2);
        Test_function(solver, filename_solver + "_fRhs2", fRhs2, sol2, tol);
        solver->SetInitialValue(0.);
        solver->SetdRightHandSide(dfRhs3);
        Test_function(solver, filename_solver + "_fRhs3", fRhs3, sol3, tol);
    }
}

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

TEST(AdamsMoultonSolver_test, GetOrder) {
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


TEST(AdamsMoultonSolver_test, EulerBackward_fRhs1) {
    double h = 0.0001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.;
    unsigned int s = 0;
    AdamsMoultonSolver solver(h, t0, t1, y0, fRhs1, dfRhs1, s);
    std::string filename_solver("test_AM_fRhs1_s1.dat");
    Test_final_results(&solver, filename_solver, sol1, 0.011);
}

TEST(AdamsMoultonSolver_test, EulerBackward_fRhs2) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 0;
    AdamsMoultonSolver solver(h, t0, t1, y0, fRhs2,dfRhs2, s);
    std::string filename_solver("test_AM_fRhs2_s1.dat");

    Test_final_results(&solver, filename_solver, sol2, 0.01);
}

TEST(AdamsMoultonSolver_test, EulerBackward_fRhs3) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.;
    unsigned int s = 0;
    AdamsMoultonSolver solver(h, t0, t1, y0, fRhs3,dfRhs3, s);
    std::string filename_solver("test_AM_fRhs3_s1.dat");
    Test_final_results(&solver, filename_solver, sol3, 0.01);
}


TEST(AdamsMoultonSolver_test, orders_and_fRhs){
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    AbstractImplicitSolver* solver = new AdamsMoultonSolver;
    solver->SetStepSize(h);
    solver->SetTimeInterval(t0, t1);
    int order_min = 1;
    int order_max = 4;
    std::string prefix_filename_solver("test_AM_");
    Test_orders(solver, order_min, order_max, prefix_filename_solver);
    delete solver;
}

// TESTS AdamsBashforth Solver:
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

TEST(AdamsBashforthSolver_test, GetOrder) {
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

TEST(AdamsBashforthSolver_test, orders_and_fRhs){
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    AbstractExplicitSolver* solver = new AdamsBashforthSolver;
    solver->SetStepSize(h);
    solver->SetTimeInterval(t0, t1);
    int order_min = 2;
    int order_max = 5;
    std::string prefix_filename_solver("test_AB_");
    Test_orders(solver, order_min, order_max, prefix_filename_solver);
    delete solver;
}

TEST(AdamsBashforthSolver_test, EulerForward_fRhs1) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.;
    unsigned int s = 1;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs1, s);
    std::string filename_solver("test_AB_fRhs1_s1.dat");
    try {
        Test_final_results(&solver, filename_solver, sol1, 0.2);
    } catch (FileNotOpenException &error) {
        error.PrintDebug();
    }
}

TEST(AdamsBashforthSolver_test, EulerForward_fRhs2) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 1;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs2, s);
    std::string filename_solver("test_AB_fRhs2_s1.dat");
    try{
        Test_final_results(&solver, filename_solver, sol2, 0.1);
    } catch (FileNotOpenException &error) {
        error.PrintDebug();
    }
}

TEST(AdamsBashforthSolver_test, EulerForward_fRhs3) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.;
    unsigned int s = 1;
    AdamsBashforthSolver solver(h, t0, t1, y0, fRhs3, s);
    std::string filename_solver("test_AB_fRhs3_s1.dat");
    try{
        Test_final_results(&solver, filename_solver, sol3, 0.1);
    } catch (FileNotOpenException &error) {
        error.PrintDebug();
    }
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

TEST(RKSolver_test, GetOrder) {
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

TEST(RKSolver_test, ProductWithA) {
    RKSolver solver;
    double ones[max_order];
    std::fill(ones, ones+max_order, 1.);
    // loop over the orders
    for(int i=1; i<max_order; i++){
        solver.SetOrder(i);
        // loop over the rows of the A matrix
        for(int j=0; j<i; j++){
        double sum = solver.ProductWithA(ones, j);
        double c_j = solver.GetC(i-1, j);
        EXPECT_DOUBLE_EQ(sum, c_j);
        }
    }
}

TEST(RKSolver_test, EulerForward_fRhs1) {
    double h = 0.0001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.;
    unsigned int s = 1;
    RKSolver solver(h, t0, t1, y0, fRhs1, s);
    std::string filename_solver("test_RK_fRhs1_s1.dat");
    try {
        Test_final_results(&solver, filename_solver, sol1, 0.1);
    } catch (FileNotOpenException &error) {
        error.PrintDebug();
    }
}

TEST(RKSolver_test, EulerForward_fRhs2) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 1;
    RKSolver solver(h, t0, t1, y0, fRhs2, s);
    std::string filename_solver("test_RK_s1.dat");
    try{
        Test_final_results(&solver, filename_solver, sol2, 0.1);
    } catch (FileNotOpenException &error) {
        error.PrintDebug();
    }
}

TEST(RKSolver_test, EulerForward_fRhs3) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.;
    unsigned int s = 1;
    RKSolver solver(h, t0, t1, y0, fRhs3, s);
    std::string filename_solver("test_RK_fRhs3_s1.dat");
    try {
        Test_final_results(&solver, filename_solver, sol3, 0.1);
    } catch (FileNotOpenException &error) {
        error.PrintDebug();
    }
}

//compare the Euler Forward methods given by RK solver and AdamsBashforth.
TEST(RKSolver_test, EulerForward_compared_to_Adamsbashforth_fRhs1) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 1;
    RKSolver solver_RK(h, t0, t1, y0, fRhs1, s);
    AdamsBashforthSolver solver_AB(h, t0, t1, y0, fRhs1, s);
    std::string filename_RK("test_RK_fRhs1_s1.dat");
    std::string filename_AB("test_AB_fRhs1_s1.dat");
    std::fstream File_AB;
    File_AB.open(filename_AB, std::ios::out);
    try {
            if (File_AB.is_open()) {
                solver_AB.SolveEquation(File_AB);
                File_AB.close();
            } else {
            throw FileNotOpenException("File cannot be opened.");
        }
    } catch (FileNotOpenException &error) {
        error.PrintDebug();
    }
    try {
        Test_results(&solver_RK, filename_RK, filename_AB);
    } catch (FileNotOpenException &error) {
        error.PrintDebug();
    }
}

TEST(RKSolver_test, EulerForward_compared_to_Adamsbashforth_fRhs2) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 1;
    RKSolver solver_RK(h, t0, t1, y0, fRhs2, s);
    AdamsBashforthSolver solver_AB(h, t0, t1, y0, fRhs2, s);
    std::string filename_RK("test_RK_fRhs2_s1.dat");
    std::string filename_AB("test_AB_fRhs2_s1.dat");
    std::fstream File_AB;
    File_AB.open(filename_AB, std::ios::out);
    try {
        if (File_AB.is_open()) {
            solver_AB.SolveEquation(File_AB);
            File_AB.close();
        } else {
            throw FileNotOpenException("File cannot be opened.");
        }
    } catch (FileNotOpenException &error) {
        error.PrintDebug();
    }
    try {
        Test_results(&solver_RK, filename_RK, filename_AB);
    } catch (FileNotOpenException &error) {
        error.PrintDebug();
    }
}

TEST(RKSolver_test, EulerForward_compared_to_Adamsbashforth_fRhs3) {
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    double y0 = 0.8;
    unsigned int s = 1;
    RKSolver solver_RK(h, t0, t1, y0, fRhs2, s);
    AdamsBashforthSolver solver_AB(h, t0, t1, y0, fRhs2, s);
    std::string filename_RK("test_RK_fRhs3_s1.dat");
    std::string filename_AB("test_AB_fRhs3_s1.dat");
    std::fstream File_AB;
    File_AB.open(filename_AB, std::ios::out);
    try {
        if (File_AB.is_open()) {
            solver_AB.SolveEquation(File_AB);
            File_AB.close();
        } else {
            throw FileNotOpenException("File cannot be opened.");
        }
    } catch (FileNotOpenException &error) {
        error.PrintDebug();
    }
    try {
        Test_results(&solver_RK, filename_RK, filename_AB);
    } catch (FileNotOpenException &error) {
        error.PrintDebug();
    }
}

TEST(RKSolver_test, orders_and_fRhs){
    double h = 0.001;
    double t0 = 0.0;
    double t1 = 100.0;
    AbstractExplicitSolver* solver = new RKSolver;
    solver->SetStepSize(h);
    solver->SetTimeInterval(t0, t1);
    int order_min = 2;
    int order_max = 4;
    std::string prefix_filename_solver("test_RK_");
    Test_orders(solver, order_min, order_max, prefix_filename_solver);
    delete solver;
}
