#ifndef JOYSTICK_H
#define JOYSTICK_H


enum Toggle { OFF = 0, ON = 1 };

#define DRIFT 45
#define ADC_RANGE 4095
#define MIDPOINT_CH1 1925
#define MIDPOINT_CH2 1880
#define SMOOTHING_MODE 0
#define FAST_BREAK ON
#define ADCPIN_CH1 A6
#define ADCPIN_CH2 A7
#define ADCPIN_CH3 A4
#define ADCPIN_CH4 A5


void joystick_pos(float* zakres1, float* zakres2, unsigned int joystick_n);


#endif
