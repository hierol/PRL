#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN  150
#define SERVOMAX  600
#define USMIN  600
#define USMAX  2400
#define SERVO_FREQ 50

int change = 0;

int cPulse0 = 300;
int cPulse1 = 300;
int cPulse2 = 300;
int cPulse3 = 300;
int cPulse4 = 300;
int cPulse5 = 300;

int c_channel = 0;


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Setup");

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);

  pinMode(25, INPUT_PULLUP); // +1
  pinMode(33, INPUT_PULLUP); // +10
  pinMode(26, INPUT_PULLUP); // -1
  pinMode(27, INPUT_PULLUP); // -10
  pinMode(32, INPUT_PULLUP); // Zmiana kanału

  for (int j=0; j<=5; j++) {pwm.setPWM(j, 0, 300);}

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(digitalRead(32));
  if (digitalRead(27) == LOW) {
    c_channel++;
    if (c_channel > 5) {c_channel=0;}
    Serial.print("Kanał serwa zmieniony na "); Serial.println(c_channel);
    delay(300);
  }


  if (digitalRead(26) == LOW) {
    change += 1;
    Serial.println(change);
  }
  else if (digitalRead(25) == LOW) {
    change += 10;
    Serial.println(change);
  }
  else if (digitalRead(33) == LOW) {
    change -= 1;
    Serial.println(change);
  }
  else if (digitalRead(32) == LOW) {
    change -= 10;
    Serial.println(change);
  }


  switch(c_channel) {
    case 0: {
      cPulse0 += change;
      pwm.setPWM(c_channel, 0, cPulse0);
      if(change!=0) {Serial.print("Sygnał serwa "); Serial.print(c_channel); Serial.print(" zmieniony na "); Serial.println(cPulse0);}
    }
    case 1: {
      cPulse1 += change;
      pwm.setPWM(c_channel, 0, cPulse1);
      if(change!=0) {Serial.print("Sygnał serwa "); Serial.print(c_channel); Serial.print(" zmieniony na "); Serial.println(cPulse1);}
    }
    case 2: {
      cPulse2 += change;
      pwm.setPWM(c_channel, 0, cPulse2);
      if(change!=0) {Serial.print("Sygnał serwa "); Serial.print(c_channel); Serial.print(" zmieniony na "); Serial.println(cPulse2);}
    }
    case 3: {
      cPulse3 += change;
      pwm.setPWM(c_channel, 0, cPulse3);
      if(change!=0) {Serial.print("Sygnał serwa "); Serial.print(c_channel); Serial.print(" zmieniony na "); Serial.println(cPulse3);}
    }
    case 4: {
      cPulse4 += change;
      pwm.setPWM(c_channel, 0, cPulse4);
      if(change!=0) {Serial.print("Sygnał serwa "); Serial.print(c_channel); Serial.print(" zmieniony na "); Serial.println(cPulse4);}
    }
    case 5: {
      cPulse5 += change;
      pwm.setPWM(c_channel, 0, cPulse5);
      if(change!=0) {Serial.print("Sygnał serwa "); Serial.print(c_channel); Serial.print(" zmieniony na "); Serial.println(cPulse5);}
    }
  }
  

  //pwm.setPWM(c_channel, 0, cPulse1); // kalibracja wybranego serwa
  change = 0;

  delay(300);
}
