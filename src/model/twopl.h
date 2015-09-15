#ifndef TWOPL_H_
#define TWOPL_H_

#include <model/model.h>

namespace irtpp
{

  class twopl : public virtual model
  {
    public:
      double probability(double theta, Matrix<double> * z)
      {
        return 0;
      }
      double * gradient(Matrix<double> * z, ll_parameter param)
      {
        return param.gradient;
      }
  };

}

#endif
