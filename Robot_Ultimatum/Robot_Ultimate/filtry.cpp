#include "utilsf.h"
#include "filtry.h"
#include <Arduino.h>


float timeDelta(unsigned long* lastTime) {
  unsigned long now = millis(); // odczyt obecnego czasu
  unsigned long delta_ms = MAX(0, now - *lastTime); // różnica czasów + zabezpieczenie
  *lastTime = now; // nadpisanie czasu ostatniego wywołania
  return (float)delta_ms/1000; // konwersja na sekundy
}


void LPFI_init(LPFI_data* data, float tau, float k) {
  data->y_n_1 = 0.0f;
  data->tau = tau;
  data->k = k;
  data->lastTime = millis();
}

void LPFII_init(LPFII_data* data, float tau, float k) {
  data->y_n_1 = 0.0f;
  data->y_n_2 = 0.0f;
  data->tau = tau;
  data->k = k;
  data->lastTime = millis();
}


void LPFI_shift_s(LPFI_data* data, float y) {
  data->y_n_1 = y;
}

void LPFII_shift_s(LPFII_data* data, float y) {
  data->y_n_2 = data->y_n_1;
  data->y_n_1 = y;
}


float LPF_I(float x, LPFI_data* data) {
  float Tp = timeDelta(&data->lastTime); // pomiar okresu wywołania
  float y = (data->k*Tp)/(data->tau + Tp)*x + data->tau/(data->tau + Tp)*data->y_n_1; // wzór filtra
  data->y_n_1 = y; // przesunięcie próbki
  return y;
}

float LPF_II(float x, LPFII_data* data) {
  float Tp = timeDelta(&data->lastTime);
  return ((data->k*SQUARE(Tp))/SQUARE(data->tau + Tp))*x + \
  ((2*data->tau)/(data->tau + Tp))*data->y_n_1 - \
  (SQUARE(data->tau)/SQUARE(data->tau + Tp))*data->y_n_2;
}
