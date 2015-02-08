#include "SamVectorize.h"
#include <math.h>

const int SIDE = 28;
const double PI = 3.14159265358979323;

void initialize_fourier(const int prow, const int pcol, float* &f) {
   float r_cosines[SIDE]; float c_cosines[SIDE]; float norm = sqrt(((float)SIDE)/2);
   for(int r=0; r<SIDE; ++r) {r_cosines[r] = cos(prow*r*PI/SIDE) / norm;}
   for(int c=0; c<SIDE; ++c) {c_cosines[c] = cos(pcol*c*PI/SIDE) / norm;}

   for(int r=0; r<SIDE; ++r) {
      for(int c=0; c<SIDE; ++c) {f[SIDE*r+c] = r_cosines[r]*c_cosines[c];}
   }
}
