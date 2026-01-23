#include "trygonomertia.h"
#include "kalibracja.h"
#include "analread.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <list>


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  ksetup();

}

void loop() {

  joystick_pos();

  pwm.setPWM(0, 0, war_s0);
  Serial.println(war_s0);

  pwm.setPWM(1, 0, war_s1);
  Serial.println(war_s1);

  pwm.setPWM(2, 0, war_s2);
  Serial.println(war_s2);

  pwm.setPWM(3, 0, war_s3);
  Serial.println(war_s3);

}

