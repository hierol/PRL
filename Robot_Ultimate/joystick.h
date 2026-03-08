#ifndef JOYSTICK_H
#define JOYSTICK_H


enum Toggle { OFF = 0, ON = 1 };

#define DRIFT 35
#define ADC_RANGE 4095
#define MIDPOINT_CH1 1925
#define MIDPOINT_CH2 1870
#define SMOOTHING_MODE 1
#define FAST_BREAK ON
#define ADCPIN_CH1 A6
#define ADCPIN_CH2 A7


void joystick_pos(float* zakres1, float* zakres2);


#endif
