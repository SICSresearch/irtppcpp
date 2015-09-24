#ifndef MODEL_H_
#define MODEL_H_

#include <type/Matrix.h>
#include <type/parameter.h>
#include <cmath>
#include <vector>

namespace irtpp
{
  class model
  {
    public:

      model(){}

      // To obtain a pointer to the static probability function
      virtual P_Function getP_Function() = 0;
      // To obtain a pointer to the static gradient function
      virtual G_Function getGrad_Function() = 0;

      static double * loglikelihood(double* z, ll_parameter param)
      {
        double * sum = new double[1];
        double tp = 0, tq = 0;
        sum[0] = 0;

        for (int k = 0; k < param.theta->nC(); ++k)
        {
          tp = param.probability((*param.theta)(0,k),z);

          if (tp < 1e-08) tp=1e-08;
          tq = 1 - tp;
          if (tq < 1e-08) tq=1e-08;

          // std::cout << "(*(param.r))(0," << k << ")→";
          // std::cout << (*(param.r))(0,k) << std::endl;
          // std::cout << "(*(param.f))(0," << k << ")→";
          // std::cout << (*(param.f))(0,k) << std::endl;

          sum[0] += (((*(param.r))(0,k))*log(tp))+(((*(param.f))(0,k)) - ((*(param.r))(0,k)))*log(tq);
        }

        sum[0] = -sum[0];

        return (sum);
      }

      virtual ~model(){}
  };

}
#endif