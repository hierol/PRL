#include "trygonomertia.h"
#include "kalibracja.h"
#include "analread.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <list>

  //set default angles
  int currentAngle_S0 = 0;
  int currentAngle_S1 = 0;
  int currentAngle_S2 = 0;
  int currentAngle_S3 = 0;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  ksetup();

}


int angleToPWM(int angle){

  if( angle > 90 ){  //clamp angle
    angle = 90;
  }
  if( angle < -90 ){
    angle = -90;
  }

  int PWM = (270/90 * angle + 380); //translate angle in deg to PWM signal
  return PWM;

}


void loop() {

  // get vlues from joystick
  joystick_pos();

  // adjust angle
  currentAngle_S1 += zakres1 * 10;

  // write to servo
  pwm.setPWM(0, 0, angleToPWM(currentAngle_S0) );
  Serial.println(angleToPWM(currentAngle_S0) );

  pwm.setPWM(1, 0, angleToPWM(currentAngle_S1) );
  Serial.println(angleToPWM(currentAngle_S1) );

  pwm.setPWM(2, 0, angleToPWM(currentAngle_S2) );
  Serial.println(angleToPWM(currentAngle_S2) );

  pwm.setPWM(3, 0, angleToPWM(currentAngle_S3) );
  Serial.println(angleToPWM(currentAngle_S3) );




// glupie sterowanie (dziala ale jest do wywalenia)
//
//  joystick_pos();
//
//  pwm.setPWM(0, 0, war_s0);
//  Serial.println(war_s0);
//
//  pwm.setPWM(1, 0, war_s1);
//  Serial.println(war_s1);
//
//  pwm.setPWM(2, 0, war_s2);
//  Serial.println(war_s2);
//
//  pwm.setPWM(3, 0, war_s3);
//  Serial.println(war_s3);

}