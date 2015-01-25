#include <math.h>    /* exp */
#include <stdlib.h>  /* srand, rand*/
#include <time.h>    /* time */
#include "VectorCSV.h"


const double reg_param = 0.000001;
double timestep = 0.00001;
const int REPS = 500;

const int K = 10;
const int test_N = 20000;
const int N = 50000; //7840;
const int thresh = N/10; // threshold under which data is for error-calc. testing; above which, for training.
const int DIM = 28*28;
VectorList xs(N, DIM);
int ts[N];
VectorList weights(10, DIM);
VectorList test_xs(test_N, DIM);
int test_ts[test_N];


//const double tau = 244.0 * exp(log(734.0/N)/734.0); // r^d/R^d=n/N => r=R*(n/N)^(1/d)
//const double tau_norm = 1.0/(sqrt(2*3.1415965358)*tau);
//double localizer(Vector &x1, Vector &x2) {
//   return tau_norm * exp(-x1.dot(x2)/(2*tau*tau));
//}
double prob(int t, Vector &x) {
   double normalizer = 0.0;
   for(int k=0; k<K; k++) { normalizer += exp(x.dot(*weights.vecs[k])); }
   return exp(x.dot(*weights.vecs[t])) / normalizer;
} double coeff(int k, int n) {
   return prob(k, *xs.vecs[n]) - (ts[n]==k ?  1 : 0);
}
void step(int k, double dt) {
   Vector grad(DIM);
   grad.zero_out();
   grad.add(*weights.vecs[k], reg_param);
   for(int n=thresh; n<N; n++) { grad.add(*xs.vecs[n], coeff(k, n)); }
   weights.vecs[k]->add(grad, -dt);
}

int classify(Vector& x) { // t of maximum probability P(t|x,w's) given predetermined w's.
   int best_k=0; double best_prob=prob(0, x);
   for(int k=1; k<K; k++) {
      double new_prob = prob(k, x);
      if(new_prob > best_prob) {
         best_k=k; best_prob=new_prob;
      }
   } return best_k;
} int error_of(Vector& x, int correct_t) {
   return (classify(x)==correct_t ? 0 : 1);
} double error_on(VectorList &test_xs, int* const &correct_ts) {
   double sum = 0.0;
   for(int n=0; n<thresh; n++) { sum += error_of(*(test_xs.vecs[n]), correct_ts[n]); }
   return sum/thresh;
}





void main() {
   /************************
    READ TRAINING DATA
    ************************/
   read_xts_from("train_usps.csv", DIM, xs, ts);
   printf("READING DONE!\n");

   /************************
    UPDATE WEIGHTS
    ************************/
   srand(time(NULL));
   //weights.zero_out();
   read_xs_from("weights.csv", DIM, weights);

   VectorList best_weights(N, DIM);
   double best_error = 1.0;

   double t = 0.0;
   for(int i=0; i<REPS; i++) {
      double error = error_on(xs, ts);
      printf("%d %f, %f %f %f\n", i, timestep, t, 1-error, 1-best_error);

      if(error < best_error) {
         printf(">"); timestep *= 1.1;
         best_weights.copy_from(weights);
         best_error = error*1.005;
      } else {
         if(timestep > 0.00001) {printf("<"); timestep *= 0.9;}
         if(rand()%4==0) {printf("!"); weights.copy_from(best_weights); }
         else {printf("~");}
      }
      //if(timestep < 0.00001 / 100) { break; } // terminate at convergence

      step(rand()%K, timestep); t += timestep;

   } int i=200; printf("%d %f, %f %f %f\n", i, timestep, t, 1-error_on(xs, ts), 1-best_error);
   printf("UPDATING DONE! terminated at time %f\n", t);

   /************************
    PREDICT TEST LABELS
    ************************/
   read_xs_from("test_usps.csv", DIM, test_xs);
   for(int n=0; n<test_N; n++) {
      test_ts[n] = classify(*test_xs.vecs[n]);
   }
   write_ts_to("Kaggle_Out_4.csv", test_N, test_ts);



   /************************
    EXIT GRACEFULLY
    ************************/
   printf("I have survived!\n");
   char c; scanf_s("%c", &c);
}
