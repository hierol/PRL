#include "joystick.h"
#include <Arduino.h>


void joystick_init(Joystick* joystick, unsigned char jx_pin, unsigned char jy_pin, unsigned char driftX, unsigned char driftY, unsigned int jx_center, unsigned int jy_center, unsigned char inv_x, unsigned char inv_y) 
{
  joystick->jx_pin = jx_pin;
  joystick->jy_pin = jy_pin;
  joystick->driftX = driftX;
  joystick->driftY = driftY;
  joystick->jx_center = jx_center;
  joystick->jy_center = jy_center;
  joystick->invert_x = inv_x;
  joystick->invert_y = inv_y;
  joystick->x = 0.0f;
  joystick->y = 0.0f;
}


void joystick_update(Joystick* joystick) 
{
  // Wyjścia znormalizowane // -1.0 <-> 1.0
  float x;
  float y;

  // Odczyt z ADC // 0.0-3.3V -> 0-4095
  int16_t rawX = analogRead(joystick->jx_pin);
  int16_t rawY = analogRead(joystick->jy_pin);

  // Wstępne przesunięcie -> pozycja środkowa joysticka = 0
  rawX -= joystick->jx_center;
  rawY -= joystick->jy_center;


  // Zerowanie DRIFTu / Strefa Nieczułości -> +-drift<CHANNEL>
  if (( rawX >= (-1*joystick->driftX) ) && ( rawX <= joystick->driftX )) {rawX=0;}
  if (( rawY >= (-1*joystick->driftY) ) && ( rawY <= joystick->driftY )) {rawY=0;}


  // Skalowanie -> Normalizacja do +-1.0
  if (rawX < 0) {
    rawX += joystick->driftX;
    x = (float)rawX / (joystick->jx_center - joystick->driftX); // rzutowanie do float
  } else if (rawX > 0) {
    rawX -= joystick->driftX;
    x = (float)rawX / (ADC_RANGE - joystick->jx_center - joystick->driftX);
  } else {x = 0.0f;}

  if (rawY < 0) {
    rawY += joystick->driftY;
    y = (float)rawY / (joystick->jy_center - joystick->driftY); // rzutowanie do float
  } else if (rawY > 0) {
    rawY -= joystick->driftY;
    y = (float)rawY / (ADC_RANGE - joystick->jy_center - joystick->driftY);
  } else {y = 0.0f;}


  // Odwracanie osi sterowania
  if (joystick->invert_x) {x *= -1.0f;}
  if (joystick->invert_y) {y *= -1.0f;}


  // Aktualizacja zmiennych
  joystick->x = x;
  joystick->y = y;


}