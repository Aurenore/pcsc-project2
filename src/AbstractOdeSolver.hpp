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

class AbstractOdeSolver {
public:
  // Constructor and destructor
  AbstractOdeSolver();
  AbstractOdeSolver(const double h, const double t0, const double t1, const double y0, double (*f)(double y, double t),
                    const unsigned int s);
  virtual ~AbstractOdeSolver();

  // Other public methods
  void SetStepSize(const double h);
  void SetTimeInterval(const double t0, const double t1);
  void SetInitialValue(const double y0);
  void SetRightHandSide(double (*f)(double y, double t));
  void SetOrder(const unsigned int s);

  double RightHandSide(double y, double t) const;
  virtual double SolveEquation(std::ostream &stream) = 0;

  // Get methods
  double GetFinalTime() const { return finalTime; }

  double GetInitialTime() const { return initialTime; }

  double GetInitialValue() const { return initialValue; }

  double GetStepSize() const { return stepSize; }

  unsigned int GetOrder() const { return s; }


private:
  double stepSize;
  double initialTime;
  double finalTime;
  double initialValue;
  double (*f_rhs)(double y, double t);

protected:
  virtual void SetB() = 0;
  unsigned int s;
  double b[max_order][max_order];
};

#endif /* ABSTRACTODESOLVER_HPP_ */
