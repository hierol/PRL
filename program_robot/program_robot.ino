#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN  150
#define SERVOMAX  600
#define USMIN  600
#define USMAX  2400
#define SERVO_FREQ 50


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void move(int servo_i, int degrees) {
  int pulseLen = map(degrees, 0, 180, SERVOMIN, SERVOMAX);
  Serial.print("Ustawiam servo "); Serial.print(servo_i); Serial.print(" na "); Serial.print(pulseLen); Serial.println("");
  pwm.setPWM(servo_i, 0, pulseLen);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Setup");

  pwm.begin();

  pwm.setPWMFreq(SERVO_FREQ);


  //for (char servo_n = 0; servo_n < 6; servo_n++) {
  //  pwm.setPWM(servonum, 0, pulselen);
  //}

  move(0, 90);
  delay(500);
  move(1, 90);
  delay(500);
  move(2, 90);
  delay(500);
  move(3, 90);
  delay(500);
  move(4, 90);
  delay(500);
  move(5, 90);
  delay(500);

  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:

  move(3, 70);
  delay(1000);
  move(3, 110);
  delay(1000);
}
