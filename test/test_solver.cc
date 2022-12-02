#include <cmath>
#include <gtest/gtest.h>
#include "src/AbstractOdeSolver.hpp"

TEST(AbstractOdeSolver_test, SetOrder) {
    AbstractOdeSolver solver;
    unsigned int s=1;
    solver.SetOrder(s);
    EXPECT_EQ(s, solver.GetOrder());
}