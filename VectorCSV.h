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
   void add(const Vector &rhs, float scale) {
      if(dim!=rhs.dim) {return;}
      for(int d=0; d<dim; d++) {sub[d] += rhs.sub[d]*scale;}
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

void read_xts_from(const char* filename, int DIM, VectorList &xs, int* const &ts) {
   FILE* train_file;
   fopen_s(&train_file, filename, "r");
   char line[10000];
   fgets(line, 10000, train_file); // read heading
   for(int n=0; n<xs.num; n++) { // read body
      fscanf_s(train_file, "%*10f,"); // (id)
      for(int d=0; d<DIM; d++) {fscanf_s(train_file, "%f,", xs.get(n, d));} // (x's)
      fscanf_s(train_file, "%1d", &ts[n]);  // (t's)

      if(n%1000==0) {printf("reading xt's: n=%d\n", n);}
   }
   fclose(train_file);
} void read_xs_from(const char* filename, int DIM, VectorList &xs) {
   FILE* train_file;
   fopen_s(&train_file, filename, "r");
   char line[10000];
   fgets(line, 10000, train_file); // read heading
   for(int n=0; n<xs.num; n++) { // read body
      fscanf_s(train_file, "%*10f,"); // (id)
      for(int d=0; d<DIM-1; d++) {fscanf_s(train_file, "%f,", xs.get(n, d));} // (x's)
      int d=DIM-1; fscanf_s(train_file, "%f", xs.get(n, d)); // (last x of row)

      if(n%1000==0) {printf("reading x's: n=%d\n", n);}
   }
   fclose(train_file);
}

void write_ts_to(const char* filename, int N, int* const &ts) {
   FILE* predict_file;
   fopen_s(&predict_file, filename, "w");

   fprintf(predict_file, "id,label\n"); // write heading
   for(int n=0; n<N; n++) { // write t's
      fprintf(predict_file, "%d,%d\n", n, ts[n]);
   }
   fclose(predict_file);
}

void write_ws_to(const char* filename, int DIM, VectorList &ws) {
   FILE* weight_file;
   fopen_s(&weight_file, filename, "w");

   for(int d=0; d<DIM-1; d++) { // write heading
      fprintf(weight_file, "%d,", d);
   } fprintf(weight_file, "%d\n", DIM-1);
   for(int n=0; n<ws.num; n++) { // write body
      for(int d=0; d<DIM-1; d++) {
         fprintf(weight_file, "%f,", ws.get(n,d));
      } fprintf(weight_file, "%f\n", ws.get(n,DIM-1));
   }
   fclose(weight_file);
}
