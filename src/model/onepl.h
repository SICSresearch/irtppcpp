#ifndef ONEPL_H_
#define ONEPL_H_

#include <model/model.h>

namespace irtpp
{

  class onepl : public virtual model
  {
  public:
    double probability(double theta, Matrix<double> * z)
    {
      double exponential = ((theta) - ((*z)(0,0)));

      if (exponential > 35)
        exponential = 35;
      else if (exponential < -35)
        exponential = -35;

      return (1 / (1.0 + exp(-exponential)));
    }

    double * gradient(Matrix<double> * z, ll_parameter param)
    {
      Matrix<double> p(param.theta->nC(), 0);
      Matrix<double> factor(param.theta->nC(), 0);

      param.gradient[0] = 0;

      for (int k = 0; k < param.theta->nC(); k++)
      {
        p(k,0) = probability((*(param.theta))(k,0), z);
        factor(k,0) = (((*(param.r))(k,0)) - ((*(param.f))(k,0))*(p(k,0)));
      }

      for (int k = 0; k < param.theta->nC(); k++ )
      {
        param.gradient[0] += factor(k,0);
      }

      return param.gradient;
    }
  };

}

#endif
