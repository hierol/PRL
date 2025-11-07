#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN  150
#define SERVOMAX  600
#define USMIN  600
#define USMAX  2400
#define SERVO_FREQ 50

int cPulse1 = 250;
int cPulse2 = 250;
int cPulse3 = 250;


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

  pinMode(26, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(digitalRead(32));
  if (digitalRead(26) == LOW) {
    cPulse1 += 1;
    Serial.println(cPulse1);
    delay(300);
  }
  else if (digitalRead(25) == LOW) {
    cPulse1 += 10;
    Serial.println(cPulse1);
    delay(300);
  }
  else if (digitalRead(33) == LOW) {
    cPulse1 -= 1;
    Serial.println(cPulse1);
    delay(300);
  }
  else if (digitalRead(32) == LOW) {
    cPulse1 -= 10;
    Serial.println(cPulse1);
    delay(300);
  }

  pwm.setPWM(5, 0, cPulse1); // kalibracja wybranego serwa

}
