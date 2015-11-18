#ifndef GPCM_H_
#define GPCM_H_

#include <estimation/estep.h>
#include <type/parameter.h>

namespace irtpp
{

  class gpcm : public model
  {
    public:

      static void boundary(double* z) {}

      Boundary_Function getBoundary_Function()
      {
        return boundary;
      }

      void transform(Matrix<double>*){}
      void untransform(Matrix<double>* z)
      {
      }

      void setInitialValues(Matrix<double>* z, dataset* data)
      {
        //ToDo
      }

      static double probability(double theta, double* z)
      {
        double exponential = exp((theta-z[1])*z[0]);

        if (exponential > 35)
          exponential = 35;
        else if (exponential < -35)
          exponential = -35;

        return exponential/(1+exponential);
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
        std::cout << "\"a\" \"b\" \"c\"" << std::endl;
        for(int i = 0; i < items; i++)
        {
          std::cout << (*z)(i, 0) << " ";
          std::cout << (*z)(i, 1) << " ";
          std::cout << 0 << std::endl;
        }
      }

      void calculateError(double& max_diff, Matrix<double>* z, Matrix<double>* z_temp, int size)
      {
        max_diff = -1;
        double t;

        for(int i = 0; i < size; i++)
        {
          t =        fabs((*z_temp)(i, 0) - (*z)(i, 0));
          max_diff = t > max_diff ? t : max_diff;
          t =        fabs((*z_temp)(i, 1) - (*z)(i, 1));
          max_diff = t > max_diff ? t : max_diff;
        }
      }
  };

}

#endif