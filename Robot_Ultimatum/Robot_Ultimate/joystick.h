#ifndef JOYSTICK_H
#define JOYSTICK_H


#define ADC_RANGE 4095


typedef struct {
  unsigned char invert_x; // odwróć oś x sterowania {0, 1}
  unsigned char invert_y; // odwróć oś y sterowania {0, 1}
  unsigned char jx_pin; // pin kanału x
  unsigned char jy_pin; // pin kanału y
  unsigned char driftX; // drift kanału x
  unsigned char driftY; // drift kanału y
  unsigned int jx_center; // wskazanie ADC przy centrum osi x
  unsigned int jy_center; // wskazanie ADC przy centrum osi y
  float x; // sterowanie kanału x znormalizowane do [-1.0 ; 1.0]
  float y; // sterowanie kanału y znormalizowane do [-1.0 ; 1.0]
} Joystick;


void joystick_init(
  Joystick* joystick, // wskaźnik na strukturę danych joysticka
  unsigned char jx_pin, // pin podłączenia kanału x joysticka
  unsigned char jy_pin, // pin podłączenia kanału y joysticka
  unsigned char driftX, // drift kanału x joysticka
  unsigned char driftY, // drift kanału y joysticka
  unsigned int jx_center, // wartość średnia kanału x przy braku sterowania
  unsigned int jy_center, // wartość średnia kanału y przy braku sterowania
  unsigned char inv_x, // flaga odwrócenia osi x
  unsigned char inv_y // flaga odwrócenia osi y
); // inicjalizacja stałych

void joystick_update(Joystick* joystick); // aktualizacja sterowania


#endif
