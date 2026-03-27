#include "board.h"
#include "buttons.h"
#include <Arduino.h>


// Buttons buttons; <- do .ino


void buttons_setup() {
  pinMode(B1L_PIN, INPUT_PULLUP);
  pinMode(B1R_PIN, INPUT_PULLUP);
  pinMode(B2L_PIN, INPUT_PULLUP);
  pinMode(B2R_PIN, INPUT_PULLUP);
}


void buttons_update(Buttons* buttons) 
{
  // Wyjścia par przycisków lewo-prawo {-1.0, 0.0, 1.0}
  float b1; // para B1L <-> B1R
  float b2; // para B2L <-> B2R


  // Kod



  // Aktualizacja zmiennych
  buttons->b1 = b1;
  buttons->b2 = b2;
}