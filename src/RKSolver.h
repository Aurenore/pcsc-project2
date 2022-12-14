//
// Created by anyam on 30.11.2022.
//

#ifndef PCSC_PROJECT_RKSOLVER_H
#define PCSC_PROJECT_RKSOLVER_H

#include "AbstractExplicitSolver.h"
#include <fstream>

/** Daughter of Abstract Explicit Solver class.
 * The Runge-Kutta solves the initial value problem
     * \f$ \frac{dy}{dt} f(t,y), \quad y(t_0) = y_0 \f$
     * In particular, the Explicit Runge-Kutta methods consist of computing for \f$ n \geq 0 \f$:
     * \f$ y_{n+1} = y_n + h \sum_{i=1}^s b_i k_i \f$
     * where for \f$ j=1, \dots, s \f$
     * \f$ k_j = f(t_n + c_j \cdot h, y_n + h (\sum_{l=0}^{j-1} a_{j-1 \; l} k_l) ). \f$
     * The coefficients \f$ a_{i \; j}, b_i, c_j \f$ are given depending of the order \f$ s \f$ and the chosen method.
     * The implemented methods with different order are:
     * order = 1: Forward Euler (first order)
     * order = 2: Explicit midpoint method
     * order = 3: Kutta's third-order method
     * order = 4: classic fourth-order method
     */
class RKSolver : public AbstractExplicitSolver {
public:
    void SolveEquation(std::ostream &stream) override;
    RKSolver();
    RKSolver(double h, double t0, double t1, double y0,
                         double (*f)(double y, double t), unsigned int s);
    ~RKSolver() override;
    void SetOrder(unsigned int order) override;

    double GetC(int i, int j) const;
    double GetA(int i, int j);

    // compute sum_{j=0}^{l-1} a[l-1][j]*k[j]
    double ProductWithA(const double k[max_order-1], int j) const;

private:
    double c[max_order-1][max_order-1];
    double a[max_order-1][max_order-1];

    void SetC();
    void SetA();

protected:
    void SetB() override;
};


#endif //PCSC_PROJECT_RKSOLVER_H
