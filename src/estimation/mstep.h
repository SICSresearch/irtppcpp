#ifndef MSTEP_H_
#define MSTEP_H_

#include <Optimization/Unrestricted/Multivariable/BFGS.hpp>
#include <type/parameter.h>
#include <model/model.h>
#include <vector>

namespace irtpp
{

  void mstep(model * m);

}

#endif