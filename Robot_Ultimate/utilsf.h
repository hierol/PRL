#ifndef UTILSF_H
#define UTILSF_H

#include <Arduino.h>


//#define log_(msg) Serial.print(msg)
//#define log_ln(msg) Serial.println(msg)
#define delay_ms(ms) delay(ms)
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

struct Arm {
  int S[6];
};

#endif
