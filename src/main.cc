#include "AbstractOdeSolver.hpp"
#include "AdamsBashforthSolver.h"
#include "RKSolver.h"
#include "AdamsMoultonSolver.h"
#include "Exception.hpp"
#include "FileNotOpenException.hpp"
#include "UncoherentValueException.h"
#include "SetOrderException.h"

#include <iostream>
#include <sstream>

double fRhs(double y, double t)  { return -100*y; }
void check_type_solver(std::string &type_solver);
void check_step_size(double &h);
void check_time_interval(double &t0, double &t1);
void check_order(unsigned int &order);
void enter_data(AbstractOdeSolver* &pSolver);
void set_data(AbstractOdeSolver* &pSolver, std::string &type_solver, double &h, double &t0, double &t1, double &y0,
              unsigned int &order);

int main(int argc, char **argv) {
    AbstractOdeSolver *pSolver;
    try {
        if (argc == 7){
            std::string type_solver;
            double h;
            double t0;
            double t1;
            double y0;
            unsigned int order;

            for(int i=0; i<7; i++) {
                std::stringstream arg(argv[i]);
                switch(i){
                    case 1:
                        arg >> type_solver;
                        break;
                    case 2:
                        arg >> h;
                        break;
                    case 3:
                        arg >> t0;
                        break;
                    case 4:
                        arg >> t1;
                        break;
                    case 5:
                        arg >> y0;
                        break;
                    case 6:
                        arg >> order;
                        break;
                }
                if(arg.fail()){
                    throw Exception("CORRUPTED_ARGUMENT", "Argument " + std::to_string(i) + " failed.");
                }
            }
            set_data(pSolver, type_solver, h, t0, t1, y0, order);

        } else if(argc == 1){
            enter_data(pSolver);
        } else {
            throw Exception("WRONG_ARGUMENTS", "Wrong number of arguments was entered.");
        }
    } catch (Exception &error) {
        error.PrintDebug();
        std::cout << "You have entered " << argc << " argument(s). Please fill the right arguments now." << std::endl;
        enter_data(pSolver);
    }

    std::cout << "solver was instantiate." << std::endl;
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
    std::cout << "finish program." << std::endl;
    delete pSolver;
    return 0;
}

void check_type_solver(std::string &type_solver){
    try{
        if(!((type_solver == "AM") || (type_solver == "AB") || (type_solver == "RK"))) {
            throw Exception("WRONG_ARGUMENTS", "Wrong string was entered as argument.");
        }
    } catch (Exception &error) {
        error.PrintDebug();
        std::cout << "Please enter the right string." << std::endl;
        std::cout << "First, choose which type of solver you would like : \n 'AM' : Adams-Moulton \n 'AB' : Adams-Bashforth \n 'RK' : Runge-Kutta: ";
        std::cin >> type_solver;
        check_type_solver(type_solver);
    }
}
void check_step_size(double &h){
    try {
        if (h<0) {
            throw UncoherentValueException("The step size must be positive.");
        }
    } catch (UncoherentValueException &error) {
        error.PrintDebug();
        std::cout << "Enter the step size h: ";
        std::cin >> h;
        check_step_size(h);
    }
    try {
        if (h<1e-6) {
            throw UncoherentValueException("The step size is too small.");
        }
    } catch (UncoherentValueException &error) {
        error.PrintDebug();
        std::cout << "Enter the step size h: ";
        std::cin >> h;
        check_step_size(h);
    }
}
void check_time_interval(double &t0, double &t1){
    try {
        if (t1<0) {
            throw UncoherentValueException("Final time cannot be negative");
        }
    } catch (UncoherentValueException &error) {
        error.PrintDebug();
        std::cout << "Enter the final time: ";
        std::cin >> t1;
        check_time_interval(t0, t1);
    }
    try {
        if (t0<0) {
            throw UncoherentValueException("Initial time cannot be negative");
        }
    } catch (UncoherentValueException &error) {
        error.PrintDebug();
        std::cout << "Enter the initial time: ";
        std::cin >> t0;
        check_time_interval(t0, t1);
    }
    try {
        if (t1<t0) {
            throw UncoherentValueException("Final time cannot be smaller than initial time.");
        }
    } catch (UncoherentValueException &error) {
        error.PrintDebug();
        std::cout << "Enter the initial time: ";
        std::cin >> t0;
        std::cout << "Enter the final time: ";
        std::cin >> t1;
        check_time_interval(t0, t1);
    }
}

void check_order(unsigned int &order){
    try {
        if (order > max_order) {
            throw SetOrderException("Order must be smaller or equal to the maximum order " + std::to_string(max_order));
        }
    } catch (SetOrderException &error) {
        std::cout << "Enter the order of the method: ";
        std::cin >> order;
        error.PrintDebug();
        check_order(order);
    }
}

void enter_data(AbstractOdeSolver *&pSolver) {
    double h;
    double t0;
    double t1;
    double y0;
    unsigned int order;
    std::string type_solver;
    std::cout << "\n                  Welcome to \n ~Abstract ODE Solver : the new generation~ \n   ---- By S. Lunven & A.-A. Mauron ---- \n" << std::endl;

    std::cout << "First, choose which type of solver you would like : \n 'AM' : Adams-Moulton \n 'AB' : Adams-Bashforth \n 'RK' : Runge-Kutta: ";
    std::cin >> type_solver;
    check_type_solver(type_solver);
    std::cout << "Enter the step size h: ";
    std::cin >> h;
    check_step_size(h);
    std::cout << "Enter the initial time: ";
    std::cin >> t0;
    std::cout << "Enter the final time: ";
    std::cin >> t1;
    check_time_interval(t0, t1);
    std::cout << "Enter the initial value: ";
    std::cin >> y0;
    std::cout << "Enter the order of the method: ";
    std::cin >> order;
    check_order(order);
    set_data(pSolver, type_solver, h, t0, t1, y0, order);
}

void set_data(AbstractOdeSolver* &pSolver, std::string &type_solver, double &h, double &t0, double &t1, double &y0,
              unsigned int &order) {
    std::cout << "You have entered the following arguments  ";
    std::cout << "\ntype solver: " << type_solver;
    std::cout << "\nh = " << h;
    std::cout << "\nt0 = " << t0;
    std::cout << "\nt1 = " << t1;
    std::cout << "\ny0 = " << y0;
    std::cout << "\norder: " << order << std::endl;

    check_type_solver(type_solver);
    if(type_solver == "AM"){
        pSolver = new AdamsMoultonSolver;
    } else if(type_solver == "AB"){
        pSolver = new AdamsBashforthSolver;
    } else if(type_solver == "RK"){
        pSolver = new RKSolver;
    } else {
        std::cerr << "No solver corresponds to type_solver." << std::endl;
    }
    check_step_size(h);
    check_time_interval(t0, t1);
    check_order(order);

    pSolver->SetStepSize(h);
    pSolver->SetTimeInterval(t0, t1);
    pSolver->SetInitialValue(y0);
    pSolver->SetRightHandSide(fRhs);
    pSolver->SetOrder(order);
}