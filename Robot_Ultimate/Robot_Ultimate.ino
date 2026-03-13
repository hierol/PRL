#include "utils.h"
#include "pwm.h"
#include "joystick.h"
#include "filtry.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


// Inicjalizacja kątów serw
int currentAngle_S0 = 0;
int currentAngle_S1 = 0;
int currentAngle_S2 = 0;
int currentAngle_S3 = 0;

float zakres1 = 0.0, zakres2 = 0.0;


void setup() {

  Serial.begin(115200);
  pwm_setup();

}


void loop() {

  // Aktualizacja sterowania -> odczyt zadanej prędkości
  joystick_pos(&zakres1, &zakres2);

  // Konwersja na kąt serwa
  currentAngle_S1 += zakres1 * 10;
  clamp_angle(&currentAngle_S1);

  // Ustawienie serw
  servo_move(0, currentAngle_S0);
  servo_move(1, currentAngle_S1);
  servo_move(2, currentAngle_S2);
  servo_move(3, currentAngle_S3);

}