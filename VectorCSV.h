// Creation 2015 by Samuel Tenka
//

#ifndef STDIO_H
#include <stdio.h>  /* all file io stuff */
#define STDIO_H
#endif

struct Vector {
   int dim;
   float* sub;
   Vector(int dim): dim(dim) {
      sub = new float[dim];
   } ~Vector() {
      delete[] sub;
   }
   void zero_out() {
      for(int d=0; d<dim; d++) { sub[d] = 0; }
   }
   void operator+=(const Vector &rhs) {
      if(dim!=rhs.dim) {return;}
      for(int d=0; d<dim; d++) {sub[d] += rhs.sub[d];}
   } Vector& times(float scale) {
      Vector scaled(dim);
      for(int d=0; d<dim; d++) {scaled.sub[d] = sub[d]*scale;}
      return scaled;
   } float dot(const Vector &rhs) {
      if(dim!=rhs.dim) {exit(-1);} // ERROR!
      float sum = 0.0;
      for(int d=0; d<dim; d++) {sum += sub[d]*rhs.sub[d];}
      return sum;
   }
};
struct VectorList {
   int num;
   Vector** vecs;
   VectorList(int num, int dim): num(num) {
      vecs = (new Vector*[num]);
      for(int n=0; n<num; n++) { vecs[n] = new Vector(dim); }
   } ~VectorList() {
      for(int n=0; n<num; n++) { delete vecs[n]; }
      delete[] vecs;
   }
   float* get(int n, int d) { return &(vecs[n]->sub[d]); }
   void zero_out() {
      for(int n=0; n<num; n++) {
         vecs[n]->zero_out();
      }
   }
};

void read_xts_from(const char* filename, int N, int DIM, VectorList &xs, int* const &ts) {
   FILE* train_file;
   fopen_s(&train_file, filename, "r");
   char line[10000];
   fgets(line, 10000, train_file); // read heading
   for(int n=0; n<N; n++) { // read body
      int DEE;
      fscanf_s(train_file, "%10f,", &DEE); // (id)
      for(int d=0; d<DIM; d++) {
         fscanf_s(train_file, "%f,", xs.get(n, d));
      } // (x's)
      fscanf_s(train_file, "%1d", &ts[n]);
      if(n%1000==0) {printf("reading: n=%d\n", n);}
   }
   fclose(train_file);
}
