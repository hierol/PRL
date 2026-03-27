#ifndef CONTROL_H
#define CONTROL_H


#define ANGLE_MAX 90.0f
#define ANGLE_MIN -90.0f

#define START_ANGLE_S0 0.0f
#define START_ANGLE_S1 0.0f
#define START_ANGLE_S2 0.0f
#define START_ANGLE_S3 0.0f
#define START_ANGLE_S4 0.0f
#define START_ANGLE_S5 0.0f


enum Toggle { OFF = 0, ON = 1 };


#define SMOOTHING ON
#define FAST_BRAKE ON


typedef struct {
  float Ki; //INIT
  float accumulator; // dokładny zcałkowany kąt
  int angle; // zcałkowany kąt całkowity
  unsigned long lastTime; // ostatnie wywołanie całki
} AngleAcc;


void control_init();
void control_update(Joystick* joy1, Joystick* joy2);


#endif
