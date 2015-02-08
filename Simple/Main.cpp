// Creation 2015 by Samuel Tenka
//

#include <stdlib.h>  /* srand, rand*/
#include <time.h>    /* time */

#include "CSV.h"
#include "SamVectorize.h"
#include "Fourier.h"

const double reg_param = 0.000001;
const double dt = 0.000001;
const int REPS = 200;

const int LEN = 7840;
const int K = 10;
//const int DIM = 28*28;
const int PDIM = 3*3;

float** xs;//[LEN][DIM]
int ts[LEN];
float** ps;//[LEN][PDIM]
float** ws;//[K][DIM]


int main() {
   construct(xs, LEN, DIM);
   construct(ps, LEN, PDIM);
   construct(ws, K, DIM);

   make_waves();
   read_xts_from("train_usps_short.csv", xs, ts, LEN, DIM);
   for(int n=0; n<LEN; n++) {
      if(n%100==0) {printf("%d\n", n);}
      fourier_analyze(xs[n], ps[n]);
   }
   write_xs_to("fouriers.csv", ps, LEN, PDIM);

   destroy(xs, LEN);
   destroy(ps, LEN);
   destroy(ws, K);
   return 0;
}
