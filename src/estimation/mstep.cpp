#include <estimation/mstep.h>

namespace irtpp
{
  void mstep(model * m, Matrix<double> & z, m_parameter param)
  {
    // Define the optimizer
    spgo::BFGS<Func, double *, ll_parameter> bfgs;
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
    p.probability   = m->getP_Function();

    // Assign the BFGS optimizer
    //bfgs = new spgo::BFGS<Func, double *, ll_parameter>();
    bfgs.setParameterSize(10);

    for (int i = 0; i < param.items; i++)
    {
      //cout << "Test status: " << ((bfgs->run(functions, z.T[i], p) == 0) ? "Success" : "-") << endl;
      bfgs.run(functions, z.memory[i], p);

      // if(z(i,0) < 0)
      //   z(i,0) = 0.851;

      // if(abs(z(i,0)) > 5)
      //   z(i,0) = 0.851;

      // if(param.dims > 1)
      // {
      //   if(abs(-z(i,1)/z(i,0)) > 5)
      //     z(i,1) = 0;

      //   if(param.dims > 2)
      //     if(abs(z(i,2)) > 5)
      //       z(i,2) = 0.5;
      //}
    }

    // Obtain the deltas
    // double maxDelta = 0;
    // for (int v1 = 0; v1 < param.items; ++v1)
    // {
    //     for(int j = 0; j < param.dims; j++)
    //         tri[j]->setIndex(0, v1, tri[j]->getIndex(0, v1) - pset[j][0][v1]);

    //     for(int j = 0; j < dims; j++)
    //         if (fabs(tri[j]->getIndex(0, v1)) > maxDelta)
    //             maxDelta = fabs(tri[j]->getIndex(0, v1));
    // }
  }

}