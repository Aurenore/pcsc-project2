//
// Created by anyam on 30.11.2022.
//

#ifndef PCSC_PROJECT_RKSOLVER_H
#define PCSC_PROJECT_RKSOLVER_H

#include "AbstractExplicitSolver.h"
#include <fstream>

class RKSolver : public AbstractExplicitSolver {
public:
    void SolveEquation(std::ostream &stream) override;
    RKSolver();
    RKSolver(double h, double t0, double t1, double y0,
                         double (*f)(double y, double t), unsigned int s);
    ~RKSolver() override;
    void SetOrder(unsigned int order) override;

    double GetC(int i, int j) const;
    double GetA(int i, int j) const;

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
