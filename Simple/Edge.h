#include "Parameters.h"
#include "SamVectorize.h"


static void shrink(const float x[], float s[]) {
   zero_out(s, HDIM);
   for(int r=0; r<HALF; ++r) {
      for(int c=0; c<HALF; ++c) {

         // avg:
         for(int i=0; i<2; ++i) {
            for(int j=0; j<2; ++j) {
            s[r*HALF+c] += x[(2*r+i)*SIDE+2*c+j];
            }
         }
         s[r*HALF+c] /= 4;

      }
   }
}

static float edginess(float a, float b) { // use harmonic mean as rounded minimum
   return (a!=0 || b!=0) ? 2*a*b/(a+b) : 0;
}
static float get_edge(int i, int j, int r, int c, const float x[]) {
   if(i!=0 || j!= 0) {
      return edginess(x[(2*r)*SIDE + 2*c],
                      x[(2*r+i)*SIDE + 2*(c+j)]);
   } return edginess(x[(2*r+1)*SIDE + 2*c],
                      x[(2*r)*SIDE + 2*(c+1)]);
}

void edge_detect(const float x[], float z[]) {
   float small[HDIM]; shrink(x, small);

   zero_out(z, XDIM); // in particular, there will be a black cross separating 4 regions
   for(int i=0; i<2; ++i) {
      for(int j=0; j<2; ++j) {

         // edge:
         for(int r=0; r<HALF-1; ++r) {
            for(int c=0; c<HALF-1; ++c) {
               z[(i*HALF+r)*SIDE + j*HALF+c] = get_edge(i,j,r,c, x);
            }
         }

      }
   }
}
