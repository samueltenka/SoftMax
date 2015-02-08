// Creation 2015 by Samuel Tenka
//

#include "CSV.h"
#include "Fourier.h"
#include "Randomize.h"
#include "SoftMax.h"
#include "Parameters.h"

const double reg_param = 0.000001;
const double dt = 0.000001;
const int REPS = 200;

float** xs;//[LEN][DIM]
int ts[LEN];
float** ps;//[LEN][PDIM]
float** ws;//[K][DIM]


int main() {
   // SET UP
   //
   construct(xs, LEN, DIM);
   construct(ps, LEN, PDIM);
   construct(ws, K, DIM);

   //seed_random();
   make_waves();
   read_xts_from("train_usps_short.csv", xs, ts, LEN, DIM);
   for(int n=0; n<LEN; n++) {fourier_analyze(xs[n], ps[n]);}
   write_xs_to("fouriers.csv", ps, LEN, PDIM);

   // SIMULATE
   //
   for(int count=0; count<REPS; ++count) {
      step(random()%K, dt, reg_param, ts, ps, ws);
      printf("hi!\n");
   }

   // CLEAN UP
   //
   destroy(xs, LEN);
   destroy(ps, LEN);
   destroy(ws, K);
   return 0;
}
