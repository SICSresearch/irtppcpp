#ifndef TWOPL_H_
#define TWOPL_H_

#include <model/model.h>

namespace irtpp
{

  class twopl : public model
  {
    public:

      void transform(Matrix<double>*){}
      void untransform(Matrix<double>*){}

      void setInitialValues(Matrix<double>* z, dataset* data)
      {
        double * result = Andrade(data);
        int ifault;

        for (int i = 0; i < data->size; i++)
        {
          (*z)(i, 0) = std::sqrt((result[1] * result[1]) / (1.0 - result[1] * result[1]));
          (*z)(i, 1) = -(ppnd(result[0], &ifault)) / result[1];
        }

        delete [] result;
      }

      static double probability(double theta, double* z)
      {
        double exponential = (z[0] * theta) + z[1];

        if (exponential > 35)
          exponential = 35;
        else if (exponential < -35)
          exponential = -35;

        return (1 / (1 + exp(-exponential)));
      }

      P_Function getP_Function()
      {
        return probability;
      }

      G_Function getGrad_Function()
      {
        return gradient;
      }

      static double* gradient(double* z, ll_parameter param)
      {
        double p;
        double factor;

        param.gradient[0] = 0;
        param.gradient[1] = 0;

        for (int k = 0; k < param.theta->nC(); k++)
        {
          p = probability((*(param.theta))(0,k), z);
          factor = (((*(param.r))(k,param.index)) - ((*(param.f))(k,0))*(p));
          
          param.gradient[0] -= factor * (*(param.theta))(0,k);
          param.gradient[1] -= factor;
        }

        return param.gradient;
      }

      Matrix<double>* getZ(int items)
      {
        return new Matrix<double>(items, 2);
      }

      int getParamSize()
      {
        return 2;
      }

      void printZ(Matrix<double>* z,  int items)
      {
        for(int i = 0; i < items; i++)
        {
          std::cout << (*z)(i, 0) << " ";
          std::cout << -(*z)(i, 1)/(*z)(i, 0) << " ";
          std::cout << 0 << std::endl;
        }
      }
  };

}

#endif
