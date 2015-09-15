#ifndef MODEL_H_
#define MODEL_H_

#include <type/Matrix.h>

namespace irtpp
{

  class model
  {
    public:
      virtual double probability(double theta, Matrix<double> * z) = 0;
      virtual void gradient(Matrix<double> *theta, Matrix<double> * z, Matrix<double> * r, Matrix<double> * f, Matrix<double> * gradient) = 0;

      double loglikelihood(Matrix<double> * theta, Matrix<double> * z, Matrix<double> * r, Matrix<double> * f)
      {
        double sum = 0, tp = 0, tq = 0;

        for (unsigned int k = 0; k < theta->nC(); ++k)
        {
          tp = probability((*theta)(k,0),z);

          if (tp < 1e-08) tp=1e-08;
          tq = 1 - tp;
          if (tq < 1e-08) tq=1e-08;

          sum += (((*r)(k,0))*log(tp))+(((*f)(k,0)) - ((*r)(k,0)))*log(tq);
        }

        return (-sum);
      }
  };

}
#endif
