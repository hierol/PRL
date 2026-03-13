# 1 "C:\\Users\\rakie\\AppData\\Local\\Temp\\tmp6qhp5m2t"
#include <Arduino.h>
# 1 "C:/Users/rakie/Documents/Arduino/PRL/main/src/main.ino"
#include "trygonomertia.h"
#include "kalibracja.h"
#include "analread.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <list>


  int currentAngle_S0 = 0;
  int currentAngle_S1 = 0;
  int currentAngle_S2 = 0;
  int currentAngle_S3 = 0;
void setup();
int angleToPWM(int angle);
void loop();
#line 15 "C:/Users/rakie/Documents/Arduino/PRL/main/src/main.ino"
void setup() {


  Serial.begin(115200);
  ksetup();

}


int angleToPWM(int angle){

  if( angle > 90 ){
    angle = 90;
  }
  if( angle < -90 ){
    angle = -90;
  }

  int PWM = (270/90 * angle + 380);
  return PWM;

}


void loop() {


  joystick_pos();


  currentAngle_S1 += zakres1 * 10;


  pwm.setPWM(0, 0, angleToPWM(currentAngle_S0) );
  Serial.println(angleToPWM(currentAngle_S0) );

  pwm.setPWM(1, 0, angleToPWM(currentAngle_S1) );
  Serial.println(angleToPWM(currentAngle_S1) );

  pwm.setPWM(2, 0, angleToPWM(currentAngle_S2) );
  Serial.println(angleToPWM(currentAngle_S2) );

  pwm.setPWM(3, 0, angleToPWM(currentAngle_S3) );
  Serial.println(angleToPWM(currentAngle_S3) );
# 79 "C:/Users/rakie/Documents/Arduino/PRL/main/src/main.ino"
}