#include "Parameters.h"

void polynomialize(const float p[], float poly[]) {
   int i=0;
   for(int j=0; j<PDIM; ++j) {
      poly[i++] = p[j];
      for(int k=j; k<PDIM; ++k) {
         poly[i++] = p[j]*p[k]/2;
      }
   }
}
