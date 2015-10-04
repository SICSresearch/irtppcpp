#ifndef THREEPL_H_
#define THREEPL_H_

#include <model/model.h>

namespace irtpp
{

  class threepl : public model
  {
    public:
      
      void transform(Matrix<double>* z)
      {
        for (int i = 0; i < z->nR(); ++i)
        {
          double qc = (*z)(i, 2);
          (*z)(i, 2) = log(qc / (1 - qc));
        }
      }

      void untransform(Matrix<double>* z)
      {
        for (int i = 0; i < z->nR(); ++i)
        {
          double qa = (*z)(i, 0);
          double qb = (*z)(i, 1);
          double qc = (*z)(i, 2);
          double ec = exp(qc);
          (*z)(i, 2) = ec / (1 + ec);
          (*z)(i, 1) = -qb / qa; //Transformacion del B   d=-b/a
        }
      }

      static double probability(double theta, double* z)
      {
        double exponential = (z[0]*theta+z[1]);

        if ( exponential > 35 )
          exponential = 35;

        else if ( exponential < -35 )
          exponential = -35;

        exponential = exp(-exponential) ;
        double ec = exp(z[2]);

        return ( (ec/(1+ec)) + (1 - (ec/(1+ec))) * (1/(1+exponential)) );
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
        double p, P_Star;
        double factor;
        double ec;      // e^c_i
        double ecp1i;   // 1 / (e^c_i + 1)
        double W;

        param.gradient[0] = 0;
        param.gradient[1] = 0;
        param.gradient[2] = 0;

        ecp1i=1/(1+exp(z[2]));
        ec=exp(z[2]);
  
        for (int k = 0; k < param.theta->nC(); k++)
        {
          p = probability((*(param.theta))(0,k), z);
          P_Star = 1/(1+exp(-(z[0]*(*(param.theta))(0,k)+z[1])));

          W = P_Star * ( 1 - P_Star ); // Numerator
          W /= p * ( 1 - p );// Denominator

          factor = (((*(param.r))(k,param.index)) - ((*(param.f))(k,0))*(p)) * W;

          param.gradient[0] -= factor * (*(param.theta))(0,k) * ecp1i;
          param.gradient[1] -= factor * ecp1i;
          param.gradient[2] -= factor * (ec * (ecp1i*ecp1i) / P_Star);
        }

        return param.gradient;
      }

      Matrix<double>* getZ(int items)
      {
        return new Matrix<double>(items, 3);
      }

      int getParamSize()
      {
        return 3;
      }

      void printZ(Matrix<double>* z,  int items)
      {
        for(int i = 0; i < items; i++)
        {
          std::cout << (*z)(i, 0) << " ";
          std::cout << (*z)(i, 1) << " ";
          std::cout << (*z)(i, 2) << std::endl;
        }
      }
  };

}

#endif
