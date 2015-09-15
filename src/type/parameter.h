#ifndef PARAM_H_
#define PARAM_H_

#include <type/Matrix.h>

namespace irtpp
{
  // Definition of a probability function
  // Name P_Function
  // 1st parameter, the theta value
  // 2nd parameter, the z parameters
  // return the result of the probability according to the model
  typedef double (*P_Function)(double, Matrix<double>*);
  
  struct ll_parameter
  {
    Matrix<double> * theta;
    Matrix<double> * r;
    Matrix<double> * f;
    double * gradient;
    P_Function probability;
  };
  // Definition of a probability function
  // Name G_Function
  // 1st parameter, the z parameters
  // 2nd parameter, the ll_parameters
  // return the result of the probability according to the model
  typedef double* (*G_Function)(Matrix<double>*, ll_parameter);

}
#endif