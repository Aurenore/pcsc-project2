
cmake_minimum_required (VERSION 3.0)
project (PCSC-project)

set(CMAKE_CXX_STANDARD 17)

add_library(pcsc
  src/pcsc.cc
)

add_subdirectory(googletest)

add_executable(main src/main.cc)
target_link_libraries(main pcsc)

add_executable(test_pcsc test/test.cc)
target_link_libraries(test_pcsc gtest_main gtest pthread pcsc)

add_custom_target(test ./test_pcsc DEPENDS test_pcsc)



add_library(solver src/AbstractOdeSolver.cpp src/AbstractOdeSolver.hpp src/AbstractExplicitSolver.cpp
        src/AbstractExplicitSolver.h src/AdamsBashforthSolver.cpp src/AdamsBashforthSolver.h
        src/RKSolver.cpp src/RKSolver.h)
add_executable(main_solver src/main.cc)
target_link_libraries(main_solver solver)

add_executable(test_solver test/test_solver.cc)
target_link_libraries(test_solver gtest_main gtest pthread solver)

add_custom_target(target_test ./test_solver DEPENDS test_solver)