#include <math.h>
#include "VectorCSV.h"



const int N = 784;//50000;
const int DIM = 28*28;
VectorList xs(N, DIM);
int ts[N];

void main() {
   /************************
    READ TRAINING DATA
    ************************/
   init_from("train_usps_shorter.csv", N, DIM, xs, ts);



   printf("I have survived!\n");
   char c; scanf_s("%c", &c);
}
