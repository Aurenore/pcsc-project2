//
// Created by anyam on 30.11.2022.
//

#ifndef PCSC_PROJECT_RKSOLVER_H
#define PCSC_PROJECT_RKSOLVER_H

#include "AbstractExplicitSolver.h"
#include <fstream>

class RKSolver : public AbstractExplicitSolver {
public:
    virtual void SolveEquation(std::ostream &stream);
    RKSolver();
    RKSolver(const double h, const double t0, const double t1, const double y0,
                         double (*f)(double y, double t), const unsigned int s);
    ~RKSolver() override;
    void SetOrder(const unsigned int order) override;

    double GetC(int i, int j) const;
    double GetA(int i, int j) const;

private:
    double c[max_order-1][max_order-1];
    double a[max_order-1][max_order-1];

    void SetC();
    void SetA();

    // compute sum_{j=0}^{l-1} a[l-1][j]*k[j]
    double ProductWithA(const double k[max_order-1], const int j) const;

protected:
    void SetB() override;
};


#endif //PCSC_PROJECT_RKSOLVER_H
