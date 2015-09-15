#include <estimation/mstep.h>

namespace irtpp
{
  typedef double* (*Func)(Matrix<double> * p, ll_parameter info);

  void mstep(model * m)
  {
    spgo::Optim<Func, Matrix<double>, ll_parameter> * test;
    // Define the vector that hold the function and the gradient
    std::vector<Func> functions;
    // Define the parameters
    ll_parameter p;

    // Store the function
    functions.push_back(m->loglikelihood);
    // Store the gradient
    functions.push_back(m->getGrad_Function());

    /*
    Matrix<double> * theta;
    Matrix<double> * r;
    Matrix<double> * f;
    double * gradient;
    P_Function probability;
    */
    // Store the values
    //p.theta = ;
    //p.r =

    // Assign the BFGS optimizer
    // test = new BFGS<Function, Parameter, Info>();
  }

}