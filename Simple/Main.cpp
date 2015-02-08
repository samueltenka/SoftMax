// Creation 2015 by Samuel Tenka
//

#include <math.h>    /* exp */
#include <stdlib.h>  /* srand, rand*/
#include <time.h>    /* time */

#ifndef VECTOR_H
#include "SamVector.h"
#define VECTOR_H
#endif
#ifndef CSV_H
#include "CSV.h"
#define CSV_H
#endif
#include "SoftMax.h"

const double reg_param = 0.000001;
const double dt = 0.000001;
const int REPS = 200;

const int K = 10;
const int N = 7840; //50000;
const int DIM = 28*28;

VectorList xs(N, DIM);
int ts[N];
VectorList weights(K, DIM);
VectorList history(REPS, 2);
void record_history(int i, double t, double error) {
   *history.get(i, 0) = t;
   *history.get(i, 1) = error;
} double get_error() {
   return error_on(xs, ts, weights);
}

void main() {
   // READ TRAINING DATA
   weights.zero_out();
   read_xs_from("weights_1.csv", DIM, weights);

   read_xts_from("train_usps_short.csv", DIM, xs, ts);
   printf("READING DONE!\n");

   // UPDATE WEIGHTS
   srand(time(NULL));
   
   double t=0.0;
   for(int i=0; i<REPS; i++) {
      step(rand()%K, dt, reg_param, ts, xs, weights);
      double error = get_error();
      t += dt;

      record_history(i, t, error);
      //if(i%20==1) {write_ws_to("history.csv", 2, history);}
      printf("%d, %f, %f, %f\n", i, t, dt, error);
   }
   printf("UPDATING DONE!");

   write_ws_to("weights.csv", DIM, weights);
   write_ws_to("history.csv", 2, history);

   // EXIT GRACEFULLY
   printf("I have survived!\n");
   char c; scanf_s("%c", &c);
}
