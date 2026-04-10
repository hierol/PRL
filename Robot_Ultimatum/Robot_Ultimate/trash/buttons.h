#ifndef BUTTONS_H
#define BUTTONS_H


#define DEBOUNCE_MS 20


typedef struct {
  float b1; // sterowanie pary przecisków B1 -> sygnały {-1.0, 0.0, 1.0}
  float b2; // sterowanie pary przecisków B2 -> sygnały {-1.0, 0.0, 1.0}
} Buttons;


void buttons_update(Buttons* buttons); // aktualizacja sterowania


#endif
