#PCSC-Solving-ODE 
Project for the *Programming concepts in scientific computing* (MATH-458) course.

This project implements different numerical methods to solve ordinary differential equations with generic non linear functions. Theses methods are divided into two categories: implicit and explicit methods. The explicit methods implemented are: Adams Bashforth  and Runge Kutta. The implicit method implemented is Adams Moulton.

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
git clone https://github.com/patrontheo/PCSC-Eigenvalue-problems.git
cd PCSC-Eigenvalue-problems
```

In order to compile it you should first install *googletest*

```
git submodule update --init 
```

Then, building is done as usual, e.g. with CLion or in the terminal:

```
mkdir build
cd build
cmake ..
make
```


