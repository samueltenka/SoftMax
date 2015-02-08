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

const int LEN = 7840; //50000;
const int K = 10;
const int DIM = 28*28;

float** xs;//[LEN][DIM]
int ts[LEN];
float** ws;//[K][DIM]


int main() {
   //construct(xs, LEN, DIM);
   construct(ws, K, DIM);

   for(int k=0; k<K; ++k) {
      initialize_fourier(k, k, ws[k]);
   }

   //read_xs_from("weights_1.csv", ws, K, DIM);
   write_xs_to("fouriers.csv", ws, K, DIM);

   //destroy(xs, LEN);
   destroy(ws, K);
   return 0;
}
