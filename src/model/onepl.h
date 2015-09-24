#ifndef ONEPL_H_
#define ONEPL_H_

#include <model/model.h>

namespace irtpp
{

  class onepl : public model
  {
  public:

    onepl(){}
    ~onepl(){}
    
    static double probability(double theta, double* z)
    {
      double exponential = ((theta) - (z[0]));

      if (exponential > 35)
        exponential = 35;
      else if (exponential < -35)
        exponential = -35;

      return (1 / (1.0 + exp(-exponential)));
    }

    P_Function getP_Function()
    {
      return probability;
    }

    G_Function getGrad_Function()
    {
      return gradient;
    }

    static double * gradient(double* z, ll_parameter param)
    {
      Matrix<double> p(param.theta->nC(), 0);
      Matrix<double> factor(param.theta->nC(), 0);

      param.gradient[0] = 0;

      for (int k = 0; k < param.theta->nC(); k++)
      {
        //std::cout << (*(param.theta))(0,k) << std::endl;
        p(k,0) = probability((*(param.theta))(0,k), z);
        factor(k,0) = (((*(param.r))(0,k)) - ((*(param.f))(0,k))*(p(k,0)));
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
