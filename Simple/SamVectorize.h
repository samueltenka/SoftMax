#ifndef SAM_VECTORIZE
#define SAM_VECTORIZE

void construct(float** &xs, const int len, const int dim) {
   xs = new float*[len];
   for(int n=0; n<len; ++n) {
      xs[n] = new float[dim];
      for(int i=0; i<dim; ++i) {xs[n][i]=0;}
   }
}
void destroy(float** &xs, const int len) {
   for(int n=0; n<len; ++n) {
      delete[] xs[n];
   }
   delete[] xs;
}

void zero_out(float a[], const int dim) {
   for(int i=0; i<dim; ++i) {a[i]=0;}
}
void add(float a[], const float b[], const double scalar, const int dim) {
   for(int i=0; i<dim; ++i) {a[i]+=b[i]*scalar;}
}
double dot(const float* &a, const float* &b, const int dim) {
   double sum = 0.0;
   for(int i=0; i<dim; ++i) {sum += a[i]*b[i];}
   return sum;
}

#endif
