#include <math.h>    /* exp */
#include <stdlib.h>  /* srand, rand*/
#include <time.h>    /* time */
#include "VectorCSV.h"


const float lambda = 0.00001;
const float timestep = 0.0001;
const int REPS = 200;

const int K = 10;
const int N = 784;//50000;
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
   for(int n=0; n<N; n++) { grad += xs.vecs[n]->times(coeff(k, n)); }
   *weights.vecs[k] += grad.times(-dt);
}

void main() {
   srand(time(NULL));

   /************************
    READ TRAINING DATA
    ************************/
   read_xts_from("train_usps_shorter.csv", N, DIM, xs, ts);
   printf("READING DONE!\n");

   /************************
    UPDATE WEIGHTS
    ************************/
   weights.zero_out();
   for(int i=0; i<REPS; i++) {
      step(rand()%K, timestep);
      if(i%10==0) {printf("%d\n", i);}
   }
   printf("UPDATING DONE!\n");

   /************************
    EXIT GRACEFULLY
    ************************/
   printf("I have survived!\n");
   char c; scanf_s("%c", &c);
}
