#include <math.h>    /* exp */
#include <stdlib.h>  /* srand, rand*/
#include <time.h>    /* time */
#include "VectorCSV.h"


const float reg_param = 0.9001;
const float timestep = 0.00001;
const int REPS = 200;

const int K = 10;
const int thresh = 5000;
const int N = 50000;
const int DIM = 28*28;
VectorList xs(N, DIM);
int ts[N];
VectorList weights(10, DIM);

float prob(int t, Vector &x) {
   float normalizer = 0.0;
   for(int k=0; k<K; k++) { normalizer += exp(x.dot(*weights.vecs[k])); }
   return exp(x.dot(*weights.vecs[t])) / normalizer;
} float coeff(int k, int n) {
   return prob(k, *xs.vecs[n]) - (ts[n]==k ?  1 : 0);
}
void step(int k, float dt) {
   Vector grad(DIM);
   grad.zero_out();
   grad.add(*weights.vecs[k], reg_param);
   for(int n=thresh; n<N; n++) { grad.add(*xs.vecs[n], coeff(k, n)); }
   weights.vecs[k]->add(grad, -dt);
}

int classify(Vector& x) { // t of maximum probability P(t|x,w's) given predetermined w's.
   int best_k=0; float best_prob=prob(0, x);
   for(int k=1; k<K; k++) {
      float new_prob = prob(k, x);
      if(new_prob > best_prob) {
         best_k=k; best_prob=new_prob;
      }
   } return best_k;
} int error_of(Vector& x, int correct_t) {
   return (classify(x)==correct_t ? 0 : 1);
} float error_on(VectorList &test_xs, int* const &correct_ts) {
   float sum = 0.0;
   for(int n=0; n<thresh; n++) { sum += error_of(*(test_xs.vecs[n]), correct_ts[n]); }
   return sum/thresh;
}

void main() {
   /************************
    READ TRAINING DATA
    ************************/
   read_xts_from("train_usps.csv", N, DIM, xs, ts);
   printf("READING DONE!\n");

   /************************
    UPDATE WEIGHTS
    ************************/
   srand(time(NULL));
   weights.zero_out();
   for(int i=0; i<REPS; i++) {
      step(rand()%K, timestep);
      if(i%5==0) {printf("%d %f\n", i, error_on(xs, ts));}
   } int i=200; {printf("%d %f\n", i, error_on(xs, ts));}
   printf("UPDATING DONE!\n");

   /************************
    EXIT GRACEFULLY
    ************************/
   printf("I have survived!\n");
   char c; scanf_s("%c", &c);
}
