#ifndef POLYTOMOUS_H_
#define POLYTOMOUS_H_

namespace irtpp
{
  class polytomous : public model
  {
  private:
  	  int* m; // Category for every item

    public:
      polytomous(){}

      // To obtain a pointer to the static probability function
      P_Function getP_Function(){}
      // To obtain a pointer to the static gradient function
      G_Function getGrad_Function(){}

      Boundary_Function getBoundary_Function(){}

      Matrix<double>* getZ(int){}

      int getParamSize(){}

      void printZ(Matrix<double>*, int){}

      void transform(Matrix<double>*){}

      void untransform(Matrix<double>*){}

      void setInitialValues(Matrix<double>*, dataset* data){}

      void calculateError(double& max_diff, Matrix<double>* z, Matrix<double>* z_temp, int size){}

      void savePrevValues(Matrix<double>* z, Matrix<double>* z_temp, int size){}

      static double probability(double theta, double* z)
      {
        double exponential = (z[0] * theta) + z[1];

        if (exponential > 35)
          exponential = 35;
        else if (exponential < -35)
          exponential = -35;

        return (1 / (1 + exp(-exponential)));
      }

      virtual ~polytomous(){}
  };

}

#endif
