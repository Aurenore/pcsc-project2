
cmake_minimum_required (VERSION 3.0)
project (PCSC-project)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)

add_library(solver src/AbstractOdeSolver.cpp src/AbstractOdeSolver.hpp src/AbstractExplicitSolver.cpp
        src/AbstractExplicitSolver.h src/AdamsBashforthSolver.cpp src/AdamsBashforthSolver.h
        src/RKSolver.cpp src/RKSolver.h src/AbstractImplicitSolver.cpp src/AbstractImplicitSolver.h
        src/AdamsMoultonSolver.cpp src/AdamsMoultonSolver.h)
add_library(exception src/Exception.cpp src/Exception.hpp src/FileNotOpenException.cpp src/FileNotOpenException.hpp
        src/UnsetOrderException.cpp src/UnsetOrderException.h src/SetOrderException.cpp src/SetOrderException.h
        src/OutOfRangeException.cpp src/OutOfRangeException.h src/UncoherentValueException.cpp src/UncoherentValueException.h src/WrongArgumentsException.cpp src/WrongArgumentsException.h src/UnsetChoiceException.cpp src/UnsetChoiceException.h)
add_executable(main_solver src/main.cc)
target_link_libraries(main_solver solver exception)

add_executable(test_solver test/test_solver.cc)
target_link_libraries(test_solver gtest_main gtest pthread solver exception)