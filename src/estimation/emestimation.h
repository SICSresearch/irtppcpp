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
#include <utils/ramsay.h>
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
        delete z_temp;

        delete[] gradient;
        delete[] sum;
        delete[] faux;
        delete[] counter_temp;
      }

      emestimation(model* m, dataset* d)
      {
        iterations =   0;
        qnodes = 40;
        Matrix<double> cuad(qnodes, 2);

        this->d = d;
        probability =  new Matrix<double>(qnodes, d->size);

        items =  d->size;
        this->m =  m;
        param_size =   m->getParamSize();

        f =            new Matrix<double>(qnodes, 1);
        r =            new Matrix<double>(qnodes, items);
        theta =    new Matrix<double>(1, qnodes);
        weight =  new Matrix<double>(1, qnodes);

        z =            m->getZ(items);
        z_temp =       m->getZ(items);
        z->reset();

        gradient =     new double[param_size]{0};
        sum =          new double[1]{0};
        faux =         new double[weight->nC()];
        counter_temp = new int[d->countItems()];

        for (int k = 0; k < qnodes; k++)
        {
          (*theta)(0, k) =  quads(qnodes)[k];
          (*weight)(0, k) = weights(qnodes)[k];
        }
        p1.f =            f;
        p1.r =            r;
        p1.weight =       weight;
        p1.probability =  probability;
        p1.d =            d;
        p1.faux =         faux;
        p1.counter_temp = counter_temp;

        p2.f =            f;
        p2.r =            r;
        p2.d =            d;
        p2.weight =       weight;
        p2.theta =        theta;
        p2.items =        items;
        p2.param_size =   param_size;
        p2.gradient =     gradient;
        p2.sum =          sum;
      }

      Matrix<double>* coef()
      {
        return z;
      }

      void updateProbabilityMatrix()
      {
        for (int k = 0; k < qnodes; k++)
        {

          for (int i = 0; i < items; i++)
          {
            (*probability)(k, i) = m->getP_Function()((*theta)(0, k), z->memory[i]);
            //std::cout << "f(" << (*theta)(0, k) << ", " << z->memory[i][0] << ") = " << (*probability)(k, i) << std::endl;
          }

          //std::cout << std::endl;
        }
      }

      void ** estimate()
      {
        void ** return_list = new void*[3];

        Matrix<double>* state[3];

        state[0] = m->getZ(items);
        state[1] = m->getZ(items);
        state[2] = m->getZ(items);

        state[0]->reset();
        state[1]->reset();
        state[2]->reset();

        bool convergenceSignal = false;

        m->setInitialValues(z, d);

        std::cout << "a b c" << std::endl;

        m->printZ(z, d->size);

        m->transform(z);

        for (;!(iterations++ > 500 || convergenceSignal);)
        {
          std::cout << iterations << std::endl;
          std::cout << "a b c" << std::endl;
          m->printZ(z, d->size);
          // Ramsay setup
          delete state[0];
          state[0] = state[1];
          state[1] = state[2];
          state[2] = m->getZ(items);
          m->savePrevValues(z, state[2], d->size);
          // Ramsay setup finished

          m->savePrevValues(z, z_temp, d->size);
          updateProbabilityMatrix();
          /**/
          std::cout << " Starting estep " << std::endl;
          estep(p1);
          std::cout << " Starting mstep " << std::endl;
          mstep(m, *z, p2);

          if(iterations > 5 && (iterations) % 3 == 0)
          {
            ramsay(state);
            m->savePrevValues(state[2], z, d->size);
          }

          /**/
          m->calculateError(max_diff, z, z_temp, d->size);
          std::cout << "mdiff : " << max_diff << std::endl;
          convergenceSignal = max_diff <=  0.0001 ? true : false;
        }

        m->untransform(z);

        m->printZ(z, d->size);

        return_list[0] = new int(iterations);
        return_list[1] = new bool(convergenceSignal);
        return_list[2] = probability;

        delete state[0];
        delete state[1];
        delete state[2];

        return return_list;
      }


private:
      int iterations;
      int qnodes;
      Input input;
      Matrix<double>* f;
      Matrix<double>* r;
      Matrix<double>* weight;
      Matrix<double>* theta;
      Matrix<double>* probability;
      Matrix<double>* z;
      Matrix<double>* z_temp;
      e_parameter     p1;
      m_parameter     p2;
      model*          m;
      dataset*        d;
      int             items;
      int             param_size;
      double          max_diff;
      double*         gradient;
      double*         sum;
      double*         faux;
      int*            counter_temp;
  };
}

#endif
