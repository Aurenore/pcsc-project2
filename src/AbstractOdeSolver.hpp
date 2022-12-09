/*
 * AbstractOdeSolver.hpp
 *
 *  Created on: Oct 25, 2012
 *      Author: rpopescu
 */

#ifndef ABSTRACTODESOLVER_HPP_
#define ABSTRACTODESOLVER_HPP_

#include <ostream>

//the maximum order of the solver is set to 5 in our case.
const unsigned int max_order = 5;

/** Abstract class, mother class of AbstractImplicitSolver and AbstractExplicitSolver. Contains all the variables and
* functions common to the implicit and explicit approaches.*/

class AbstractOdeSolver {
public:
  // Constructor and destructor
  AbstractOdeSolver();
  AbstractOdeSolver(double h, double t0, double t1, double y0, double (*f)(double y, double t),
                    unsigned int s);
  virtual ~AbstractOdeSolver();

  // Other public methods
  void SetStepSize(double h);
  void SetTimeInterval(double t0, double t1);
  void SetInitialValue(double y0);
  void SetRightHandSide(double (*f)(double y, double t));
  virtual void SetOrder(unsigned int order);

  double RightHandSide(double y, double t) const;
  double ScalarProduct(int size, const double* a, const double* b) const;
  //Product with B : return sum_{i = 0}^{j-1} F[i]*b[j-1][i]
  double ProductWithB(const double F[max_order+1], int j) const;
  /** Virtual function, overriden in the daughter classes, computing the numerical solution of the ODE.*/
  virtual void SolveEquation(std::ostream &stream) = 0;

  // Get methods
  double GetFinalTime() const { return finalTime; }

  double GetInitialTime() const { return initialTime; }

  double GetInitialValue() const { return initialValue; }

  double GetStepSize() const { return stepSize; }

  unsigned int GetOrder() const { return s; }

  virtual double GetB(const unsigned int i, const unsigned int j) const;

private:
  double stepSize;
  double initialTime;
  double finalTime;
  double initialValue;
  double (*f_rhs)(double y, double t);


protected:
    unsigned int s;
    /** Virtual function, overriden in the daughter classes, setting the coefficients values b[i][j]  of the equations to solve .*/
    virtual void SetB() = 0;
    double b[max_order][max_order+1];
};

#endif /* ABSTRACTODESOLVER_HPP_ */
