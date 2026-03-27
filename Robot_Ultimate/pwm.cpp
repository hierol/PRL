#include "pwm.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


static Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


void pwm_setup() {
  Serial.println("PWM: Setup");

  int init_pwm = angle_to_pwm(DEFAULT_ANGLE);

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);

  for (int n=0; n<6; n++) { pwm.setPWM(n, 0, init_pwm); }

  Serial.println("PWM: Done");
}


void servo_move(unsigned char servo_n, int degrees) {
  clamp_angle(&degrees); // Zabezpieczenie
  int pulseLen = angle_to_pwm(degrees);

  Serial.print("Ustawiam serwo ");
  Serial.print(servo_n); Serial.print(" na "); Serial.println(pulseLen);

  pwm.setPWM(servo_n, 0, pulseLen);
}


void clamp_angle(int* angle) {
  int _angle = *angle;
  if ( _angle > DEGMAX ) { *angle = DEGMAX; } // 90
  if ( _angle < DEGMIN ) { *angle = DEGMIN; } // -90
}


int angle_to_pwm(int angle) {
  int pulseLen = map(angle, DEGMIN, DEGMAX, SERVOMIN, SERVOMAX);
  return pulseLen;
}
