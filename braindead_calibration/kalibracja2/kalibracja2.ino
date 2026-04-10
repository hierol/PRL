#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN  150
#define SERVOMAX  600
#define USMIN  600
#define USMAX  2400
#define SERVO_FREQ 50

#define PIN_CH 25
#define PIN_1P 26
#define PIN_10P 19
#define PIN_1N 27
#define PIN_10N 18


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

  pinMode(PIN_1P, INPUT_PULLUP); // +1
  pinMode(PIN_10P, INPUT_PULLUP); // +10
  pinMode(PIN_1N, INPUT_PULLUP); // -1
  pinMode(PIN_10N, INPUT_PULLUP); // -10
  pinMode(PIN_CH, INPUT_PULLUP); // Zmiana kanału

  for (int j=0; j<=5; j++) {pwm.setPWM(j, 0, 300);}

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(digitalRead(PIN_CH));
  if (digitalRead(PIN_CH) == LOW) {
    c_channel++;
    if (c_channel > 5) {c_channel=0;}
    Serial.print("Kanał serwa zmieniony na "); Serial.println(c_channel);
    delay(300);
  }


  if (digitalRead(PIN_1P) == LOW) {
    change += 1;
    Serial.println(change);
  }
  else if (digitalRead(PIN_10P) == LOW) {
    change += 10;
    Serial.println(change);
  }
  else if (digitalRead(PIN_1N) == LOW) {
    change -= 1;
    Serial.println(change);
  }
  else if (digitalRead(PIN_10N) == LOW) {
    change -= 10;
    Serial.println(change);
  }


  switch(c_channel) {
    case 0: {
      cPulse0 += change;
      pwm.setPWM(c_channel, 0, cPulse0);
      if(change!=0) {Serial.print("Sygnał serwa "); Serial.print(c_channel); Serial.print(" zmieniony na "); Serial.println(cPulse0);}
      break;
    }
    case 1: {
      cPulse1 += change;
      pwm.setPWM(c_channel, 0, cPulse1);
      if(change!=0) {Serial.print("Sygnał serwa "); Serial.print(c_channel); Serial.print(" zmieniony na "); Serial.println(cPulse1);}
      break;
    }
    case 2: {
      cPulse2 += change;
      pwm.setPWM(c_channel, 0, cPulse2);
      if(change!=0) {Serial.print("Sygnał serwa "); Serial.print(c_channel); Serial.print(" zmieniony na "); Serial.println(cPulse2);}
      break;
    }
    case 3: {
      cPulse3 += change;
      pwm.setPWM(c_channel, 0, cPulse3);
      if(change!=0) {Serial.print("Sygnał serwa "); Serial.print(c_channel); Serial.print(" zmieniony na "); Serial.println(cPulse3);}
      break;
    }
    case 4: {
      cPulse4 += change;
      pwm.setPWM(c_channel, 0, cPulse4);
      if(change!=0) {Serial.print("Sygnał serwa "); Serial.print(c_channel); Serial.print(" zmieniony na "); Serial.println(cPulse4);}
      break;
    }
    case 5: {
      cPulse5 += change;
      pwm.setPWM(c_channel, 0, cPulse5);
      if(change!=0) {Serial.print("Sygnał serwa "); Serial.print(c_channel); Serial.print(" zmieniony na "); Serial.println(cPulse5);}
      break;
    }
  }
  

  //pwm.setPWM(c_channel, 0, cPulse1); // kalibracja wybranego serwa
  change = 0;

  delay(300);
}
