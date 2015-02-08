// Creation 2015 by Samuel Tenka
//

#ifndef STDIO_H
#include <stdio.h>  /* all file io stuff */
#define STDIO_H
#endif


void read_xts_from(const char* filename, float** &xs, int* &ts, const int len, const int dim) {
   FILE* train_file;
   fopen_s(&train_file, filename, "r");
   char line[10000];
   fgets(line, 10000, train_file); // read heading
   for(int n=0; n<len; ++n) { // read body
      fscanf_s(train_file, "%*10f,"); // (id)
      for(int i=0; i<dim; ++i) {fscanf_s(train_file, "%f,", &xs[n][i]);} // (x's)
      fscanf_s(train_file, "%1d", &ts[n]);  // (t's)

      if(n%1000==0) {printf("reading xt's: n=%d\n", n);}
   }
   fclose(train_file);
} void read_xs_from(const char* filename, float** &xs, const int len, const int dim) {
   FILE* train_file;
   fopen_s(&train_file, filename, "r");
   char line[10000];
   fgets(line, 10000, train_file); // read heading
   for(int n=0; n<len; ++n) { // read body
      fscanf_s(train_file, "%*10f,"); // (id)
      int i; for(i=0; i<dim-1; ++i) {fscanf_s(train_file, "%f,", &xs[n][i]);} // (x's)
      fscanf_s(train_file, "%f", &xs[n][i]); // (last x of row)

      if(n%1000==0) {printf("reading x's: n=%d\n", n);}
   }
   fclose(train_file);
}

void write_ts_to(const char* filename, int* &ts, const int len) {
   FILE* predict_file;
   fopen_s(&predict_file, filename, "w");

   fprintf(predict_file, "id,label\n"); // write heading
   for(int n=0; n<len; ++n) { // write t's
      fprintf(predict_file, "%d,%d\n", n, ts[n]);
   }
   fclose(predict_file);
}

void write_xs_to(const char* filename, float** &xs, const int len, const int dim) {
   FILE* weight_file;
   fopen_s(&weight_file, filename, "w");

   fprintf(weight_file, "id,"); // write heading
   int i; for(i=0; i<dim-1; ++i) {
      fprintf(weight_file, "%d,", i);
   } fprintf(weight_file, "%d\n", i);

   for(int n=0; n<len; n++) { // write body
      fprintf(weight_file, "%d,", n);
      int i; for(i=0; i<dim-1; ++i) {
         fprintf(weight_file, "%f,", xs[n][i]);
      } fprintf(weight_file, "%f\n", xs[n][i]);
   }
   fclose(weight_file);
}
