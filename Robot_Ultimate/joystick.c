#include "joystick.h"
#include "utils.h"
#include "filtry.h"
#include <Arduino.h>


static unsigned long lastTime1 = 0; // ostatni pomiar -> gdy T~
static unsigned long lastTime2 = 0;
static const float T = 0.1; // okres wywołania [sekundy]
static float zakres1_n_1 = 0.0; // poprzednia próbka
static float zakres2_n_1 = 0.0;
static float zakres1_n_2 = 0.0; // 2 próbki wstecz
static float zakres2_n_2 = 0.0;


static float timeDelta(unsigned long* lastTime) {
  unsigned long now = millis();
  unsigned long delta_ms = MAX(0, now - *lastTime);
  *lastTime = now;
  return (float)delta_ms/1000;
}


void joystick_pos(float* zakres1, float* zakres2) 
{
  // Odczyt z ADC // 0.0-3.3V -> 0-4095
  int16_t channel1 = analogRead (ADCPIN_CH1);
  int16_t channel2 = analogRead (ADCPIN_CH2);


  // Wstępne przesunięcie -> pozycja środkowa joysticka = 0
  channel1 -= MIDPOINT_CH1; // midpoint ~ 1925
  channel2 -= MIDPOINT_CH2; // midpoint ~ 1870


  // Zerowanie DRIFTu / Strefa Nieczułości -> +-35
  if (( channel1 >= (-1*DRIFT) ) && ( channel1 <= DRIFT )) {channel1=0;}
  if (( channel2 >= (-1*DRIFT) ) && ( channel2 <= DRIFT )) {channel2=0;}


  // Skalowanie -> Normalizacja do +-1.0
  if (channel1 < 0) {
    channel1 += DRIFT;
    _zakres1 = (float)channel1 / (MIDPOINT_CH1 - DRIFT); // rzutowanie do float
  } else if (channel1 > 0) {
    channel1 -= DRIFT;
    _zakres1 = (float)channel1 / (MIDPOINT_CH1 - ADC_RANGE - DRIFT);
  } else {_zakres1 = 0.0;}

  if (channel2 < 0) {
    channel2 += DRIFT;
    _zakres2 = (float)channel2 / (MIDPOINT_CH2 - DRIFT);
  } else if (channel2 > 0) {
    channel2 -= DRIFT;
    _zakres2 = (float)channel2 / (MIDPOINT_CH2 - ADC_RANGE - DRIFT);
  } else {_zakres2 = 0.0;}


  // Wygładzanie sterowania -> Filtr Dolnoprzepustowy
  switch (SMOOTHING_MODE) {
    case 0: {
      // pass
      break;
    }
    case 1: {
      // Sprawdzenie czy obecny sygnał nie jest słabszy od poprzedniego
      unsigned char BREAKING1 = abs(_zakres1) < abs(zakres1_n_1); // |u(n)| < |u(n-1)|
      unsigned char BREAKING2 = abs(_zakres2) < abs(zakres2_n_1);

      // Przy szybkim hamowaniu -> omiń filtr
      if (!BREAKING1 || !FAST_BREAK) {
      _zakres1 = LPF_I(_zakres1, zakres1_n_1, timeDelta(&lastTime1), 1.0);
      }
      if (!BREAKING2 || !FAST_BREAK) {
      _zakres2 = LPF_I(_zakres2, zakres2_n_1, timeDelta(&lastTime2), 1.0);
      }
      
      // Przesunięcie próbek pod następną iterację
      zakres1_n_1 = _zakres1;
      zakres2_n_1 = _zakres2;
      break;
    }
    case 2: {
      // Sprawdzenie czy obecny sygnał nie jest słabszy od poprzedniego
      unsigned char BREAKING1 = abs(_zakres1) < abs(zakres1_n_1); // |u(n)| < |u(n-1)|
      unsigned char BREAKING2 = abs(_zakres2) < abs(zakres2_n_1);

      // Przy szybkim hamowaniu -> omiń filtr
      if (!BREAKING1 || !FAST_BREAK) {
      _zakres1 = LPF_II(_zakres1, zakres1_n_1, zakres1_n_2, timeDelta(&lastTime1), 1.0);
      }
      if (!BREAKING2 || !FAST_BREAK) {
      _zakres2 = LPF_II(_zakres2, zakres2_n_1, zakres2_n_2, timeDelta(&lastTime2), 1.0);
      }
      
      // Przesunięcie próbek pod następną iterację
      zakres1_n_2 = zakres1_n_1;
      zakres1_n_1 = _zakres1;
      zakres2_n_2 = zakres2_n_1;
      zakres2_n_1 = _zakres2;
      break;
    }
    default:
      // pass
  }


  // Aktualizacja zmiennych
  *zakres1 = _zakres1;
  *zakres2 = _zakres2;


  // Logowanie danych
  log_("kanał 1 => sterowanie: "); log_(_zakres1, 3); log_(" | ADC: "); log_ln(channel1);
  log_("kanał 2 => sterowanie: "); log_(_zakres2, 3); log_(" | ADC: "); log_ln(channel2);
  log_ln("+==========+");
  delay_ms((int)(T*1000)); // 100ms
}