#ifndef VECTOR_H
#include "SamVector.h"
#define VECTOR_H
#endif

#include <math.h>


double prob(int t, const Vector &x, const VectorList &weights) {
   double normalizer = 0.0;
   for(int k=0; k<weights.num; k++) { normalizer += exp(x.dot(*weights.vecs[k])); }
   return exp(x.dot(*weights.vecs[t])) / normalizer;
} double coeff(int n, int k, const int* const ts, const VectorList &xs, const VectorList &weights) {
   return prob(k, *xs.vecs[n], weights) - (ts[n]==k ?  1 : 0);
} void step(int k, double dt, double reg_param, const int* const ts, const VectorList &xs, const VectorList &weights) {
   Vector grad(weights.vecs[0]->dim);
   grad.zero_out();
   grad.add(*weights.vecs[k], reg_param);
   for(int n=0; n<xs.num; n++) {
      grad.add(*xs.vecs[n], coeff(n, k, ts, xs, weights));
   }
   weights.vecs[k]->add(grad, -dt);
}

int classify(const Vector& x, const VectorList &weights) { // t of maximum probability P(t|x,w's) given predetermined w's.
   int best_k=0; double best_prob=prob(0, x, weights);
   for(int k=1; k<K; k++) {
      double new_prob = prob(k, x, weights);
      if(new_prob >= best_prob) {
         best_k=k; best_prob=new_prob;
      }
   } return best_k;
} int error_of(const Vector& x, const int correct_t, const VectorList &weights) {
   return (classify(x, weights)==correct_t ? 0 : 1);
} double error_on(const VectorList &test_xs, const int* const &correct_ts, const VectorList &weights) {
   double sum = 0.0;
   for(int n=0; n<test_xs.num; n++) { sum += error_of(*(test_xs.vecs[n]), correct_ts[n], weights); }
   return sum/test_xs.num;
}
