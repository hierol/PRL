#include "pwm.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


static Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


void pwm_setup() {
  Serial.println("PWM: Setup");

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);

  Serial.println("PWM: Done");
}


void servo_move(unsigned char servo_n, int degrees) {
  clamp_angle(&degrees); // Zabezpieczenie
  int pulseLen = angle_to_pwm(servo_n, degrees); // konwersja kąta na ilość kwantów okna pwm

  Serial.print("Ustawiam serwo ");
  Serial.print(servo_n); Serial.print(" na "); Serial.println(pulseLen); // pulseLen albo degrees

  pwm.setPWM(servo_n, 0, pulseLen);
}


void clamp_angle(int* angle) {
  int _angle = *angle;
  if ( _angle > DEGMAX ) { *angle = DEGMAX; } // 90
  if ( _angle < DEGMIN ) { *angle = DEGMIN; } // -90
}


int angle_to_pwm(unsigned char servo_n, int angle) {
  int pulseLen;

  switch (servo_n) {
    case 0: {
      pulseLen = map(angle, DEGMIN, DEGMAX, S0_MIN, S0_MAX);
      break;
    }
    case 1: {
      pulseLen = map(angle, DEGMIN, DEGMAX, S1_MIN, S1_MAX);
      break;
    }
    case 2: {
      pulseLen = map(angle, DEGMIN, DEGMAX, S2_MIN, S2_MAX);
      break;
    }
    case 3: {
      pulseLen = map(angle, DEGMIN, DEGMAX, S3_MIN, S3_MAX);
      break;
    }
    case 4: {
      pulseLen = map(angle, DEGMIN, DEGMAX, S4_MIN, S4_MAX);
      break;
    }
    case 5: {
      pulseLen = map(angle, DEGMIN, DEGMAX, S5_MIN, S5_MAX);
      break;
    }
  }
  
  return pulseLen;
}
