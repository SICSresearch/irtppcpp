#ifndef TWOPL_H_
#define TWOPL_H_

namespace irtpp
{

  class twopl : public model
  {
    public:
      double probability(double theta, Matrix<double> * z)
      {
        return 0;
      }
      void gradient(Matrix<double> * theta, Matrix<double> * z, Matrix<double> * r, Matrix<double> * f, Matrix<double> * gradient)
      {
        ;
      }
  };

}

#endif
