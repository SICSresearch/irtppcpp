#ifndef ONEPL_H_
#define ONEPL_H_

#include <model/model.h>

namespace irtpp
{

  class onepl : public model
  {
    public:

      void transform(Matrix<double>*){}
      void untransform(Matrix<double>*){}
    
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
          p(k,0) = probability((*(param.theta))(0,k), z);
          factor(k,0) = (((*(param.r))(k,param.index)) - ((*(param.f))(k,0))*(p(k,0)));
        }

        for (int k = 0; k < param.theta->nC(); k++ )
        {
          param.gradient[0] += factor(k,0);
        }

        return param.gradient;
      }

      Matrix<double>* getZ(int items)
      {
        return new Matrix<double>(items, 1);
      }

      int getParamSize()
      {
        return 1;
      }

      void printZ(Matrix<double>* z, int items)
      {
        for(int i = 0; i < items; i++)
        {
          std::cout << 1 << " ";
          std::cout << (*z)(i, 0) << " ";
          std::cout << 0 << std::endl;
        }
      }
  };

}

#endif