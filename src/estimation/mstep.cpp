#include <estimation/mstep.h>

using namespace spgo;

namespace irtpp
{

typedef double* (*Function)(Matrix<double> p, ll_parameter info);

  void mstep()
  {
    Optim<Function, Matrix<double>, ll_parameter> * test;
    // Define the vector that hold the function and the gradient
    vector<Function> f;
    // Define the parameters
    ll_parameter p;

    // Store the function
    f.push_back(function);
    // Store the gradient
    // f.push_back(gradient);

    // Store the initial values
    // p.push_back(100);
    // p.push_back(100);

    // Assign the BFGS optimizer
    // test = new BFGS<Function, Parameter, Info>();
  }

}