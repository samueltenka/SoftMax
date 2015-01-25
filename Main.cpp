#include <stdio.h>

const int N = 50000;
const int DIM = 28*28;
struct Vector {
   double s[DIM];
};

void main() {
   Vector* xs[N];
   FILE* train_file;
   fopen_s(&train_file, "train_usps.csv", "r");
   char temp[1000];
   for(int d=0; d<DIM; d++) {
      fscanf_s(train_file, "%s,", &temp);
   }
   for(int n=0; n<N; n++) {
      for(int d=0; d<DIM; d++) {
         fscanf_s(train_file, "%f[,\n]", &(xs[n]->s[d]));
      }
   }
   printf("I have survived!\n");
}
