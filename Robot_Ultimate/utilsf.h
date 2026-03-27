#ifndef UTILSF_H
#define UTILSF_H


#define log_(msg) Serial.print(msg)
#define log_ln(msg) Serial.println(msg)
#define logf_(float_, n) Serial.print(float_, n)
#define logf_ln(float_, n) Serial.println(float_, n)

#define delay_ms(ms) delay(ms)
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define ABS(x) ((x)>0?(x):-(x))

struct Arm {
  int S[6];
};

#endif
