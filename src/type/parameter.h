#ifndef PARAM_H_
#define PARAM_H_

#include <type/Matrix.h>

namespace irtpp
{

  struct ll_parameter
  {
    Matrix<double> * theta;
    Matrix<double> * r;
    Matrix<double> * f;
    double * gradient;
  };

}
#endif