#ifndef FILTRY_H
#define FILTRY_H


#define SQUARE(val) ((val) * (val))


float LPF_I(float x, float y_n_1, float Tp, float tau);
float LPF_II(float x, float y_n_1, float y_n_2, float Tp, float tau);


#endif
