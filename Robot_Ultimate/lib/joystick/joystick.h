#ifndef JOYSTICK_H
#define JOYSTICK_H


enum Toggle { OFF = 0, ON = 1 };

#define DRIFT 170
#define ADC_RANGE 4095
#define MIDPOINT_CH1 1925
#define MIDPOINT_CH2 1880
#define SMOOTHING_MODE 1
#define FAST_BREAK ON
#define ADCPIN_CH1 34
#define ADCPIN_CH2 35
#define ADCPIN_CH3 32
#define ADCPIN_CH4 33


void joystick_pos(float* zakres1, float* zakres2, unsigned int joystick_n);


#endif
