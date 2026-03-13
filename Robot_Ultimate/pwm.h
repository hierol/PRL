#ifndef PWM_H
#define PWM_H


#define DEGMIN -90
#define DEGMAX 90
#define DEFAULT_ANGLE 0

#define SERVOMIN  150
#define SERVOMAX  600
#define USMIN  600
#define USMAX  2400
#define SERVO_FREQ 50


void pwm_setup();
void servo_move(unsigned char servo_n, int degrees);
void clamp_angle(int* angle);
int angle_to_pwm(int angle);


#endif
