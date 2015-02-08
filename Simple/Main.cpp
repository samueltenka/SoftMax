// Creation 2015 by Samuel Tenka
//

#include "CSV.h"
#include "SamVectorize.h"
#include "Fourier.h"
#include "Randomize.h"
#include "SoftMax.h"
#include "Parameters.h"
#include "Poly.h"

const double reg_param = 0.0000001;
const double dt = 0.000001;
const int REPS = 200;

float** xs;//[LEN][XDIM]
int ts[LEN];
float** ps;//[LEN][MDIM]
float** qs;//[LEN][QDIM]
float** ws;//[K][DIM]


int main() {
   // SET UP
   //
   construct(xs, LEN, XDIM);
   construct(ps, LEN, MDIM);
   //construct(qs, LEN, QDIM);
   construct(ws, K, DIM);

   seed_random();
   make_waves();
   read_xts_from("train_usps_short.csv", xs, ts, LEN, XDIM);
   for(int n=0; n<LEN; n++) {
      fourier_analyze(xs[n], ps[n]);
      polynomialize(ps[n], qs[n]);
   }
   //write_xs_to("features.csv", qs, LEN, QDIM);

   // SIMULATE
   //
   float wtemp[DIM]; double last_error=1.0;
   for(int count=0; count<REPS; ++count) {
      int k = random()%K;
      times(wtemp, ws[k], 1.0, DIM);

      step(k, dt, reg_param, ts, ps, ws);

      double e = error_on(ts, ps, ws, LEN);
      if(e>last_error && random()%10!=0) {times(ws[k], wtemp, 1.0, DIM);}
      else {last_error = e;}
      
      printf("%d \t %f \t %f\n", count, last_error, e);
   }
   write_xs_to("weights_.csv", ws, K, DIM);

   // CLEAN UP
   //
   destroy(xs, LEN);
   destroy(ps, LEN);
   //destroy(qs, LEN);
   destroy(ws, K);
   return 0;
}
