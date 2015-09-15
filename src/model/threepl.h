#ifndef THREEPL_H_
#define THREEPL_H_

#include <model/model.h>

namespace irtpp
{

  class threepl : public model
  {
    public:
      static double probability(double theta, Matrix<double> * z)
      {
        return 0;
      }

      P_Function getP_Function()
      {
        return probability;
      }

      G_Function getGrad_Function()
      {
        return gradient;
      }

      static double * gradient(Matrix<double> * z, ll_parameter param)
      {
        return param.gradient;
      }
  };

}

#endif
