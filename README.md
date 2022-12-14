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
git clone https://github.com/Aurenore/pcsc-project2.git
cd pcsc-project2
```

Install *googletest*
```
git submodule update --init 
```

##Build CMake porject:
```
mkdir build
cd build
cmake ..
make
```


