#ifndef EMESTIMATION_H_
#define EMESTIMATION_H_

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

namespace irtpp
{
  class emestimation
  {
    public:
      ~emestimation()
      {
      	delete m;
        delete f;
        delete r;
        delete weight;
        delete theta;
        delete probability;
        delete z;
        delete d;
        delete [] gradient;
        delete [] sum;
        delete [] faux;
        delete [] counter_temp;
      }

      emestimation(char* file, model * m)
      {
        iterations = 0;
        Matrix<double> cuad(41, 2);
        input.importCSV((char *) "Cuads.csv", cuad, 1, 0);

        d =           new dataset(0);
        input.importCSV(file, *d, 1, 0);
        probability = new Matrix<double>(41, d->size);

        items =       d->size;
        this->m =     m;
        param_size =  m->getParamSize();

        f =           new Matrix<double>(41, 1);
        r =           new Matrix<double>(41, items);
        theta =       new Matrix<double>(1, 41);
        weight =      new Matrix<double>(1, 41);

        z =           m->getZ(items);
        z->reset();

        gradient =     new double[param_size]{0};
        sum =          new double[1]{0};
        faux =         new double[weight->nC()];
        counter_temp = new int[d->countItems()];

        for (int k = 0; k < cuad.nR(); k++)
        {
          (*theta)(0, k) =  cuad(k, 0);
          (*weight)(0, k) = cuad(k, 1);
        }

        p1.f =            f;
        p1.r =            r;
        p1.weight =       weight;
        p1.probability =  probability;
        p1.d =            d;
        p1.faux =         faux;
        p1.counter_temp = counter_temp;

        p2.f =           f;	
        p2.r =           r;
        p2.d =           d;
        p2.weight =      weight;
        p2.theta =       theta;
        p2.items =       items;
        p2.param_size =  param_size;
        p2.gradient =    gradient;
        p2.sum =         sum;
      }

      void estimate()
      {
        m->transform(z);

        for (;!(iterations++ > 500);)
        {
          //cout << iterations << endl;

          for (int k = 0; k < 41; k++)
          {
            for (int i = 0; i < items; i++)
            {
              (*probability)(k, i) = m->getP_Function()((*theta)(0, k), z->memory[i]);
            }
          }

          estep(p1);
          mstep(m, *z, p2);
        }

        m->untransform(z);

        m->printZ(z, d->size);
      }

    private:
      Input input;
      int iterations;

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
      int             param_size;
      double*         gradient;
      double*         sum;
      double*         faux;
      int*            counter_temp;
  };
}

#endif