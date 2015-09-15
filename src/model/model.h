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

      virtual double probability(double theta, Matrix<double> * z) = 0;
      virtual double * gradient(Matrix<double> * z, ll_parameter param) = 0;

      double * loglikelihood(Matrix<double> * z, ll_parameter param)
      {
        double * sum = new double[1];
        double tp = 0, tq = 0;
        sum[0] = 0;

        for (int k = 0; k < param.theta->nC(); ++k)
        {
          tp = probability((*param.theta)(k,0),z);

          if (tp < 1e-08) tp=1e-08;
          tq = 1 - tp;
          if (tq < 1e-08) tq=1e-08;

          sum[0] += (((*(param.r))(k,0))*log(tp))+(((*(param.f))(k,0)) - ((*(param.r))(k,0)))*log(tq);
        }

        sum[0] = -sum[0];

        return (sum);
      }

      virtual ~model();
  };

}
#endif
