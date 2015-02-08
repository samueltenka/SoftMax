#include <math.h>

const int LEN = 7840;
const int DIM = 28*28;
const int K = 10;

void zero_out(double a[], const int len) {
   for(int i=0; i<len; ++i) {a[i]=0;}
} void add(double a[], const double b[], const double scalar, const int len) {
   for(int i=0; i<len; ++i) {a[i]+=b[i]*scalar;}
} double dot(const double a[], const double b[], const int len) {
   double sum = 0.0;
   for(int i=0; i<len; ++i) {sum += a[i]*b[i];}
   return sum;
}

double prob(const int t, const double x[], const double* weights[]) {
   double partition = 0.0;
   double boltzmann = 0.0;
   for(int k=0; k<K; k++) {
      double b = exp(dot(x, weights[k], DIM));
      if(k==t) {boltzmann=b;}
      partition += b;
   }
   return boltzmann / partition;
} double nk_error(int n, int k, const int ts[], const double* xs[], const double* weights[]) {
   return prob(k, xs[n], weights) - (ts[n]==k ?  1 : 0);
} void step(int k, double dt, double reg_param, const int ts[], const double* xs[], double* weights[]) {
   double grad[DIM]; zero_out(grad, DIM);
   add(grad, weights[k], reg_param, DIM);
   for(int n=0; n<LEN; ++n) {
      add(grad, xs[n], nk_error(n,k,ts,xs,weights), DIM);
   }
   add(weights[k], grad, -dt, DIM);
}

int classify(const double x[], const double* weights[]) { // t of maximum probability P(t|x,w's) given predetermined w's.
   int best_k=0; double best_prob=prob(0,x,weights);
   for(int k=1; k<K; ++k) {
      double new_prob = prob(k, x, weights);
      if(new_prob >= best_prob) {best_k=k; best_prob=new_prob;}
   }
   return best_k;
} int error_of(const int correct_t, const double x[], const double* weights[]) {
   return (classify(x, weights)==correct_t ? 0 : 1);
} double error_on(const int correct_ts[], const double* test_xs[], const double* weights[], int len) {
   double sum = 0.0;
   for(int n=0; n<len; n++) {sum += error_of(correct_ts[n], test_xs[n], weights);}
   return sum/len;
}
