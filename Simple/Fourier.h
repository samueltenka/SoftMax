#include "SamVectorize.h"
#include "Parameters.h"
#include <math.h>


float waves[PSIDE][PSIDE][DIM];

static void initialize_fourier(const int prow, const int pcol, float f[]) {
   float r_cosines[SIDE]; float c_cosines[SIDE]; float norm = sqrt(((float)SIDE)/2);
   for(int r=0; r<SIDE; ++r) {r_cosines[r] = cos(prow*r*PI/SIDE) / norm;}
   for(int c=0; c<SIDE; ++c) {c_cosines[c] = cos(pcol*c*PI/SIDE) / norm;}

   for(int r=0; r<SIDE; ++r) {
      for(int c=0; c<SIDE; ++c) {f[SIDE*r+c] = r_cosines[r]*c_cosines[c];}
   }
}
void make_waves() {
   for(int prow=0; prow<PSIDE; ++prow) {
      for(int pcol=0; pcol<PSIDE; ++pcol) {
         initialize_fourier(prow, pcol, waves[prow][pcol]);
      }
   }
}

void fourier_analyze(const float x[], float p[]) {
   for(int prow=0; prow<PSIDE; ++prow) {
      for(int pcol=0; pcol<PSIDE; ++pcol) {
         p[prow*PSIDE+pcol] = dot(waves[prow][pcol], x, DIM);
      }
   }
}
