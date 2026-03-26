#include <filtry.h>


float LPF_I(float x, float y_n_1, float Tp, float tau) {
  unsigned char k = 1;
  return (k*Tp)/(tau + Tp)*x + tau/(tau + Tp)*y_n_1;
}


float LPF_II(float x, float y_n_1, float y_n_2, float Tp, float tau) {
  unsigned char k = 1;
  return ((k*SQUARE(Tp))/SQUARE(tau + Tp))*x + ((2*tau)/(tau + Tp))*y_n_1 - (SQUARE(tau)/SQUARE(tau + Tp))*y_n_2;
}
