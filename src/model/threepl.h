#ifndef THREEPL_H_
#define THREEPL_H_

#include <model/model.h>

namespace irtpp
{

  class threepl : public virtual model
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
