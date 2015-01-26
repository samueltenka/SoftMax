// Creation 2015 by Samuel Tenka
//

#ifndef STDIO_H
#include <stdio.h>  /* all file io stuff */
#define STDIO_H
#endif

#ifndef VECTOR_H
#include "SamVector.h"
#define VECTOR_H
#endif

void read_xts_from(const char* filename, int DIM, VectorList &xs, int* const &ts) {
   FILE* train_file = fopen(filename, "r");
   char line[10000];
   fgets(line, 10000, train_file); // read heading
   for(int n=0; n<xs.num; n++) { // read body
      fscanf(train_file, "%*10f,"); // (id)
      for(int d=0; d<DIM; d++) {fscanf(train_file, "%f,", xs.get(n, d));} // (x's)
      fscanf(train_file, "%1d", &ts[n]);  // (t's)

      if(n%1000==0) {printf("reading xt's: n=%d\n", n);}
   }
   fclose(train_file);
}

void write_ws_to(const char* filename, int DIM, VectorList &ws) {
   FILE* weight_file = fopen(filename, "w");
   fprintf(weight_file, "id,"); // write heading
   for(int d=0; d<DIM-1; d++) {
      fprintf(weight_file, "%d,", d);
   } fprintf(weight_file, "%d\n", DIM-1);

   for(int n=0; n<ws.num; n++) { // write body
      fprintf(weight_file, "%d,", n);
      for(int d=0; d<DIM-1; d++) {
         fprintf(weight_file, "%f,", *ws.get(n,d));
      } fprintf(weight_file, "%f\n", *ws.get(n,DIM-1));
   }
   fclose(weight_file);
}
