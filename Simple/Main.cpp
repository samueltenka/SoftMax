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

const double reg_param = 0.000001;
const double dt = 0.00001;
const int REPS = 200;

const int K = 10;
const int N = 50000;
const int DIM = 28*28;

VectorList xs(N, DIM);
int ts[N];
VectorList weights(K, DIM);
VectorList history(REPS, 2);

#include "SoftMax.h"

void main() {
   // READ TRAINING DATA
   read_xts_from("train_usps_short.csv", DIM, xs, ts);
   printf("READING DONE!\n");

   // UPDATE WEIGHTS
   srand(time(NULL));
   weights.zero_out();

   double t=0.0;
   for(int i=0; i<REPS; i++) {
      *history.get(i, 0) = t;
      *history.get(i, 1) = error_on(xs, ts, weights);
      printf("%d, %f, %f, %f\n", i, dt, t, *history.get(i, 1));
      step(rand()%K, dt, reg_param, ts, xs, weights); t += dt;
   }
   printf("UPDATING DONE!");

   write_ws_to("history.csv", 2, history);

   // EXIT GRACEFULLY
   printf("I have survived!\n");
   char c; scanf_s("%c", &c);
}
