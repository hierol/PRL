#ifndef JOYSTICK_H
#define JOYSTICK_H


#define ADC_RANGE 4095


typedef struct {
  unsigned char jx_pin; // pin kanału x
  unsigned char jy_pin; // pin kanału y
  unsigned char driftX; // drift kanału x
  unsigned char driftY; // drift kanału y
  unsigned int jx_center; // wskazanie ADC przy centrum osi x
  unsigned int jy_center; // wskazanie ADC przy centrum osi y
  float x; // sterowanie kanału x znormalizowane do [-1.0 ; 1.0]
  float y; // sterowanie kanału y znormalizowane do [-1.0 ; 1.0]
} Joystick;


void joystick_init(Joystick* joystick, unsigned char jx_pin, unsigned char jy_pin, unsigned char driftX, unsigned char driftY, unsigned int jx_center, unsigned int jy_center); // inicjalizacja stałych
void joystick_update(Joystick* joystick); // aktualizacja sterowania


#endif
