#ifndef PWM_H
#define PWM_H


#define DEGMIN -90
#define DEGMAX 90

//#define SERVOMIN  150
//#define SERVOMAX  600
//#define USMIN  600
//#define USMAX  2400
#define SERVO_FREQ 50

#define S0_MIN 190
#define S0_MAX 540

#define S1_MIN 205
#define S1_MAX 540

#define S2_MIN 115
#define S2_MAX 630

#define S3_MIN 125
#define S3_MAX 625

#define S4_MIN 125
#define S4_MAX 630

#define S5_MIN 115
#define S5_MAX 625


void pwm_setup();
void servo_move(unsigned char servo_n, int degrees);
void clamp_angle(int* angle);
int angle_to_pwm(unsigned char servo_n, int angle);


#endif
