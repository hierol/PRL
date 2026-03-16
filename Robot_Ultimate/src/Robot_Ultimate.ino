#include <utilsf.h>
#include <pwm.h>
#include <joystick.h>
#include <filtry.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Inicjalizacja kątów serw
Arm currentAngle = {{0, 0, 0, 0, 0, 0}};


float zakres1 = 0.0, zakres2 = 0.0;
float zakres3 = 0.0, zakres4 = 0.0;


void setup() {

  Serial.begin(115200);
  pwm_setup();

}


void loop() {

  // Aktualizacja sterowania -> odczyt zadanej prędkości
  joystick_pos(&zakres1, &zakres2, 0);
  joystick_pos(&zakres3, &zakres4, 1);

  // Konwersja na kąt serwa
  currentAngle.S[3] += zakres1 * 10;
  clamp_angle(&currentAngle.S[3]);

  currentAngle.S[4] += zakres2 * 10;
  clamp_angle(&currentAngle.S[4]);

  currentAngle.S[5] += zakres3 * 10;
  clamp_angle(&currentAngle.S[5]);

  currentAngle.S[5] += zakres4 * 10;
  clamp_angle(&currentAngle.S[5]);

  // Ustawienie serw
  for (int n=0; n<6; n++) {
    servo_move(n, currentAngle.S[n]);
  }


  delay(100);

}