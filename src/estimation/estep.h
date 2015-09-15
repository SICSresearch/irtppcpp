#ifndef ESTEP_H_
#define ESTEP_H_

#include <model/onepl.h>
#include <model/twopl.h>
#include <model/threepl.h>
#include <type/Matrix.h>
#include <type/dataset.h>

namespace irtpp
{

  void estep(model * m, Matrix<double> * f, Matrix<double> * r, Matrix<double> * weights, dataset * d);

}

#endif