#ifndef FILTRY_H
#define FILTRY_H


#define SQUARE(val) ((val) * (val))


typedef struct {
  float y_n_1; // poprzednia próbka
  float tau; // stała czasowa
  float k; // wzmocnienie
  unsigned long lastTime; // ostatnie wywołanie (w ms od uruchomienia kodu)
} LPFI_data;

typedef struct {
  float y_n_1;
  float y_n_2;
  float tau;
  float k;
  unsigned long lastTime;
} LPFII_data;


float timeDelta(unsigned long* lastTime);

void LPFI_init(LPFI_data* data, float tau, float k);
void LPFII_init(LPFII_data* data, float tau, float k);

void LPFI_shift_s(LPFI_data* data, float y);
void LPFII_shift_s(LPFII_data* data, float y);

float LPF_I(float x, LPFI_data* data);
float LPF_II(float x, LPFII_data* data);


#endif
