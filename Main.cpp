#include <stdio.h>


struct Vector {
   int dim;
   float* sub;
   Vector(int dim): dim(dim) {
      sub = new float[dim];
   } ~Vector() {
      delete[] sub;
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
};


const int N = 784;//7830;//50000;
const int DIM = 28*28;

void main() {
   /************************
    READ TRAINING DATA
    ************************/
   VectorList xs(N, DIM);
   int ts[N];

   FILE* train_file;
   fopen_s(&train_file, "train_usps_shorter.csv", "r");
   char line[10000];
   fgets(line, 10000, train_file); // read heading
   for(int n=0; n<N; n++) { // read body
      //fgets(line, 10000, train_file);
      int DEE;
      fscanf_s(train_file, "%10f,", &DEE); // (id)
      ////printf("!%d\n", DEE);
      for(int d=0; d<DIM; d++) {
         fscanf_s(train_file, "%f,", xs.get(n, d));
         ////printf("!!%10f\n", *xs.get(n,d));
      } // (x's)
      char X;
      fscanf_s(train_file, "%c", &X);//ts[n]); // (t)
      ////printf("!!!%c\n", X);
      if(n%1000==0) {printf("!%d\n", n);}
   }
   printf("%f %f\n", *xs.get(0, 0), *xs.get(N-1, 157));
   fclose(train_file);

   printf("I have survived!\n");
   char c; scanf_s("%c", &c);
}
