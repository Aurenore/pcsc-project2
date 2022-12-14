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
#include <cmath>

int CHOICE;
double fRhs(double y,double t){
    try{
        if (CHOICE==1) {
            return 1 + t;
        } else if (CHOICE==2) {
            return -100*y;
        } else if(CHOICE==3){
            return sin(t)*cos(t);
        } else {
            throw Exception("UNSET_CHOICE", "The choice was not set, therefore fRhs could not be called");
        }
    } catch (Exception &error) {
        error.PrintDebug();
        std::cout << "Choice is set to 1." << std::endl;
        CHOICE = 1;
        return 1 + t;
    }
}
double dfRhs(double y, double t) {
    try {
        if (CHOICE == 1) {
            return 0;
        } else if (CHOICE == 2) {
            return -100;
        } else if (CHOICE == 3) {
            return 0;
        } else {
            throw Exception("UNSET_CHOICE", "The choice was not set, therefore dfRhs could not be called");
        }
    } catch (Exception &error) {
        error.PrintDebug();
        std::cout << "Choice is set to 1." << std::endl;
        CHOICE = 1;
        return 0;
    }
}

void check_type_solver(std::string &type_solver);
void check_step_size(double &h);
void check_time_interval(double &t0, double &t1);
void check_order(unsigned int &order);
void check_choice(int &choice);
void enter_data(AbstractOdeSolver* &pSolver);
void set_data(AbstractOdeSolver* &pSolver, std::string &type_solver, double &h, double &t0, double &t1, double &y0,
              unsigned int &order, int &choice);

int main(int argc, char **argv) {
    AbstractOdeSolver *pSolver;
    try {
        if (argc == 8){
            // the right number of arguments was given by the user.
            std::string type_solver;
            double h;
            double t0;
            double t1;
            double y0;
            unsigned int order;
            int choice;

            for(int i=0; i<8; i++) {
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
                    case 7:
                        arg >> choice;
                        break;
                }
                if(arg.fail()){
                    throw Exception("CORRUPTED_ARGUMENT", "Argument " + std::to_string(i) + " failed.");
                }
            }
            set_data(pSolver, type_solver, h, t0, t1, y0, order, choice);

        } else if(argc == 1){
            // no argument was given by the user.
            enter_data(pSolver);
        } else {
            throw Exception("WRONG_ARGUMENTS", "Wrong number of arguments was entered.");
        }
    } catch (Exception &error) {
        error.PrintDebug();
        std::cout << "You have entered " << argc << " argument(s). Please fill the right arguments now." << std::endl;
        enter_data(pSolver);
    }

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
    std::cout << "The solution is stored in " + filename_solver << std::endl;
    delete pSolver;
    return 0;
}

void check_type_solver(std::string &type_solver){
    /*!
     * Check if the given type solver is coherent.
    * \param type_solver: string of the type of solver.
     * For Adams-Moulton: "AM"
     * For Adams-Bashforth: "AB"
     * For Runge-Kutta: "RK"
    */
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
    /*!
     * Check if the given step size is coherent.
    * \param h : step size.
    */
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
    /*!
     * Check if the given time interval is coherent.
    * \param t0: initial time
     * \param t1: final time
    */
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
    /*!
     * Check if the given order is coherent.
    * \param order: order of the method.
    */
    try {
        if (order > max_order) {
            throw SetOrderException("Order must be smaller or equal to the maximum order " + std::to_string(max_order));
        }
    } catch (SetOrderException &error) {
        error.PrintDebug();
        std::cout << "Enter the order of the method: ";
        std::cin >> order;
        check_order(order);
    }
}

void check_choice(int &choice){
    /*!
     * Check if the given choice is coherent.
    * \param choice : choice of the function. It should be 1, 2 or 3.
    */
    try {
        if (!(choice == 1 || choice == 2 || choice == 3)){
            throw UncoherentValueException("Choice must be either 1, 2, or 3.");
        }
    } catch (UncoherentValueException &error) {
        error.PrintDebug();
        std::cout<< "Please enter the function you want among these functions:" <<std::endl;
        std::cout <<"1: f(y,t) = 1+t" <<std::endl;
        std::cout<<"2: f(y,t) = -100*y" <<std::endl;
        std::cout<<"3: f(y,t) = sin(t)*cos(t)" <<std::endl;
        std::cout<<"You choose function number:";
        std::cin>>choice;
        check_choice(choice);
    }
}

void enter_data(AbstractOdeSolver *&pSolver) {
    /*!
     * Let the user enter the arguments of the solver.
    * \param pSolver: Abstract ODE solver pointer.
    */
    double h;
    double t0;
    double t1;
    double y0;
    unsigned int order;
    int choice;
    std::string type_solver;
    std::cout << "\n                  Welcome to \n ~Abstract ODE Solver : the new generation~ \n   ---- By S. Lunven & A.-A. Mauron ---- \n" << std::endl;

    std::cout << "First, choose which type of solver you would like : \n 'AM' : Adams-Moulton \n 'AB' : Adams-Bashforth \n 'RK' : Runge-Kutta: " << std::endl;
    std::cout << "Your solver: ";
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
    std::cout<< "Please enter the function you want among these functions:" <<std::endl;
    std::cout <<"1: f(y,t) = 1+t" <<std::endl;
    std::cout<<"2: f(y,t) = -100*y" <<std::endl;
    std::cout<<"3: f(y,t) = sin(t)*cos(t)" <<std::endl;
    std::cout<<"You choose function number:";
    std::cin>>choice;
    check_choice(choice);
    set_data(pSolver, type_solver, h, t0, t1, y0, order, choice);
}

void set_data(AbstractOdeSolver* &pSolver, std::string &type_solver, double &h, double &t0, double &t1, double &y0,
              unsigned int &order, int &choice) {
    /*!
     * Check if the arguments are coherent. Then set the solver with them.
    * \param pSolver: Abstract ODE solver pointer.
     * \param type_solver: string indicating the type of the solver.
     * \param h: step size
     * \param t0: initial time
     * \param t1: final time
     * \param y0: initial value
     * \param order: order of the method
     * \param choice: choice of the right hand side function.
    */
    std::cout << "You have entered the following arguments  ";
    std::cout << "\ntype solver: " << type_solver;
    std::cout << "\nh = " << h;
    std::cout << "\nt0 = " << t0;
    std::cout << "\nt1 = " << t1;
    std::cout << "\ny0 = " << y0;
    std::cout << "\norder: " << order;
    std::cout << "\nchoice: " << choice << std::endl;
    check_type_solver(type_solver);
    if(type_solver == "AM"){
        AdamsMoultonSolver* pSolverTemp = new AdamsMoultonSolver;
        pSolverTemp->SetdRightHandSide(dfRhs);
        pSolver = pSolverTemp;
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
    check_choice(choice);

    pSolver->SetStepSize(h);
    pSolver->SetTimeInterval(t0, t1);
    pSolver->SetInitialValue(y0);
    pSolver->SetRightHandSide(fRhs);
    pSolver->SetOrder(order);
    CHOICE = choice;
}