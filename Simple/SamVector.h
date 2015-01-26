// Creation 2015 by Samuel Tenka
//

struct Vector {
   int dim;
   float* sub;
   Vector(int dim): dim(dim) {
      sub = new float[dim];
   } ~Vector() {
      delete[] sub;
   } void zero_out() {
      for(int d=0; d<dim; d++) { sub[d] = 0; }
   } void add(const Vector &rhs, float scale) {
      if(dim!=rhs.dim) {return;}
      for(int d=0; d<dim; d++) {sub[d] += rhs.sub[d]*scale;}
   } float dot(const Vector &rhs) const {
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
