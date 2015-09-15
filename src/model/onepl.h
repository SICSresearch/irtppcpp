#ifndef ONEPL_H_
#define ONEPL_H_

namespace irtpp
{

  class onepl : public model
  {
  public:
    double probability(double theta, Matrix<double> * z)
    {
      double exponential = ((theta) - ((*z)(0,0)));

      if (exponential > 35)
        exponential = 35;
      else if (exponential < -35)
        exponential = -35;

      return (1 / (1.0 + exp(-exponential)));
    }

    void gradient(Matrix<double> * theta, Matrix<double> * z, Matrix<double> * r, Matrix<double> * f, Matrix<double> * gradient)
    {
      Matrix<double> p(theta->nC(), 0);
      Matrix<double> factor(theta->nC(), 0);

      gradient->reset();

      for (unsigned int k = 0; k < theta->nC(); k++)
      {
        p(k,0) = probability((*theta)(k,0), z);
        factor(k,0) = (((*r)(k,0)) - ((*f)(k,0))*(p(k,0)));
      }

      for (unsigned int k = 0; k < theta->nC(); k++ )
      {
        ((*gradient)(0,0)) += factor(k,0);
      }
    }
  };

}

#endif
