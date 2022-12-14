#PCSC-Solving-ODE 
Project for the *Programming concepts in scientific computing* (MATH-458) course.

This project implements different numerical methods to solve ordinary differential equations with generic non linear functions: y'(t) = f(y,t)
Theses methods are divided into two categories: implicit and explicit methods. The explicit methods implemented are: Adams Bashforth  and Runge Kutta. The implicit method implemented is Adams Moulton.

All these methods return the numerical solution of the ODE. 

The implemented classes are described in the following diagram: 
METTRE LE DIAGRAMME

##Prerequisites:
*'C++17'
*'Doxygen'
*'GoogleTest'

##Installation

Clone the repo:
```
git clone https://github.com/Aurenore/pcsc-project2.git
cd pcsc-project2
```

Install *googletest*
```
git submodule update --init 
```

##Build CMake project:
```
mkdir build
cd build
cmake ..
make
```
##Create Doxygen documentation
Install Doxygen: https://www.doxygen.nl/manual/install.html

To view documentation: LIEN HTML

##Usage
###Command line arguments
The user can provide different options:
`--solver`: to specify the method used to find the solution of the ODE: Moulton, Bashforth or Runge Kutta
`--h`: step size 
`--t0`: initial time
`--t1`: final time
`--y0`: initial value
`--order`: order of the method: [0,4] for Adams Moulton Solver, [1,5] for Adams Bashforth Solver and [1,4] for the Runge Kutta Solver
`--choice`: Three functions f(y,t) are provided to the user. Choice is the number assoicated to the function the user wants to use so 1,2 or three

As an example the following command will solve the ODE associated to function number 2 (f(y,t)=-100*y) using the Runge Kutta solver of order 3. The initial time is set to 0 and the final time to 100. The step size used is 0.001 and the initial guess is 1.
`./main --solver RK --h 0.001 --t0 0 --t1 100 --y0 1 --order 3 --choice 2`

###Output
The time and the numerical solution at each time steps can be found in the 'cmake-build-debug/solution_file.dat VERIFIER NOM

##List of features
* Changable numerical methods to solve ODE
* Changable initial conditions for which to solve the ODE
* Easy addition of new functions for which to solve the ODE

##Tests
GoogleTest library was used.
The tests can be found in `test/test.cc` file.  
To run the tests: COMPLETER






