#include <estimation/mstep.h>

namespace irtpp
{
  void mstep(model * m, Matrix<double> & z, m_parameter param)
  {
    // Define the vector that hold the function and the gradient
    std::vector<Func> functions;
    // Define the parameters
    ll_parameter p;

    // Store the function and the gradient
    functions.push_back(m->loglikelihood);
    functions.push_back(m->getGrad_Function());

    // Store the values
    p.r             = param.r;
    p.f             = param.f;
    p.theta         = param.theta;
    p.gradient      = param.gradient;
    p.sum           = param.sum;
    p.probability   = m->getP_Function();

    for (int i = 0; i < param.items; i++)
    {
      spgo::BFGS<Func, double *, ll_parameter> bfgs;
      bfgs.setParameterSize(param.param_size);
      //std::cout << "Item → " << i << std::endl;
      p.index = i;
      bfgs.run(functions, z.memory[i], p);
    }
  }

}