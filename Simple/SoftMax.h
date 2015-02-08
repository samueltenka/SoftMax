#include <math.h>
#include "SamVectorize.h"

const int LEN = 7840;
const int DIM = 28*28;
const int K = 10;

double prob(const int t, const float* &x, const float** &weights) {
   double partition = 0.0;
   double boltzmann = 0.0;
   for(int k=0; k<K; k++) {
      double b = exp(dot(x, weights[k], DIM));
      if(k==t) {boltzmann=b;}
      partition += b;
   }
   return boltzmann / partition;
} double nk_error(int n, int k, const int* &ts, const float** &xs, const float** &weights) {
   return prob(k, xs[n], weights) - (ts[n]==k ?  1 : 0);
} void step(const int k, const double dt, const double reg_param, const int* &ts, const float** &xs, float* &weights[]) {
   float grad[DIM]; zero_out(grad, DIM);
   add(grad, weights[k], reg_param, DIM);
   for(int n=0; n<LEN; ++n) {
      add(grad, xs[n], nk_error(n,k,ts,xs,weights), DIM);
   }
   add(weights[k], grad, -dt, DIM);
}

int classify(const float* &x, const float** &weights) { // t of maximum probability P(t|x,w's) given predetermined w's.
   int best_k=0; double best_prob=prob(0,x,weights);
   for(int k=1; k<K; ++k) {
      double new_prob = prob(k, x, weights);
      if(new_prob >= best_prob) {best_k=k; best_prob=new_prob;}
   }
   return best_k;
} int error_of(const int correct_t, const float* &x, const float** &weights) {
   return (classify(x, weights)==correct_t ? 0 : 1);
} double error_on(const int* &correct_ts, const float** &test_xs, const float** &weights, int len) {
   double sum = 0.0;
   for(int n=0; n<len; n++) {sum += error_of(correct_ts[n], test_xs[n], weights);}
   return sum/len;
}
