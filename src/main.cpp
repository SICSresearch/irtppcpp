#include <iostream>
#include <model/onepl.h>
#include <model/twopl.h>
#include <model/threepl.h>
#include <type/Matrix.h>
#include <type/dataset.h>
#include <type/parameter.h>
#include <estimation/estep.h>
#include <estimation/mstep.h>
#include <type/ghquads.h>
#include <utils/Input.h>

using namespace irtpp;
using std::cout;
using std::endl;

int main(int argc, char ** argv)
{
  Input input;
  int iterations;
  iterations = 0;

  /**/
  Matrix<double> cuad(41, 2);
  input.importCSV((char *) "Cuads.csv", cuad, 1, 0);
  /**/

  Matrix<double>* f;
  Matrix<double>* r;
  Matrix<double>* weight;
  Matrix<double>* theta;
  Matrix<double>* probability;
  Matrix<double>* z;
  e_parameter     p1;
  m_parameter     p2;
  model*          m;
  dataset*        d;
  int             items;
  int             dims;
  double		  theta_d;

  d = new dataset(0);
  input.importCSV(argv[1], *d, 1, 0);
  probability = new Matrix<double>(41, d->size);

  items = d->size;
  dims = 1;
  m = new onepl();

  f = new Matrix<double>(1, 41);
  r = new Matrix<double>(41, items);
  theta = new Matrix<double>(1, 41);
  weight = new Matrix<double>(1, 41);

  z = new Matrix<double>(items, 3);
  z->reset();

  for (int k = 0; k < cuad.nR(); k++)
  {
    (*theta)(0, k) = cuad(k, 0);
    (*weight)(0, k) = cuad(k, 1);
  }

  for (int k = 0; k < 41; k++)
  {
    for (int i = 0; i < items; i++)
    {
      theta_d = (*theta)(0, k);
      //cout << "(" << 0 << ", " << k << ")" << theta_d << endl;
      (*probability)(k, i) = m->getP_Function()(theta_d, z->memory[i]);
    }
  }

  p1.f = f;
  p1.r = r;
  p1.weights = weight;
  p1.probability = probability;
  p1.d = d;

  p2.f = f;	
  p2.r = r;
  p2.d = d;
  p2.weights = weight;
  p2.theta = theta;
  p2.items = items;
  p2.dims = dims;
  p2.gradient = new double[1]{0};

  for (;!(iterations++ > 200);)
  {
//  cout << iterations << endl;
  	estep(p1);
  	mstep(m, *z, p2);
  }

  for(int i = 0; i < d->size; i++)
  {
  	cout << (*z)(i, 0) << " ";
  	cout << (*z)(i, 1) << " ";
    cout << (*z)(i, 2) << endl;
  }
  
  cout << "Gradient: " << p2.gradient[0] << endl;

  return 0;
}
