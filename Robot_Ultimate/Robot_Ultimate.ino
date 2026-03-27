#include "utilsf.h"
#include "board.h"
#include "pwm.h"
#include "joystick.h"
#include "control.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "dance.h"
#include "toolsteer.h"

// Instancje joysticka
Joystick J1;
Joystick J2;


void setup() {

  Serial.begin(115200);
  pwm_setup();
  dance_setup();

  joystick_init(&J1, ADCPIN_J1X, ADCPIN_J1Y, 45, 45, 1900, 1900); // (*joystick, jx_pin, jy_pin, driftX, driftY, jx_center, jy_center)
  joystick_init(&J2, ADCPIN_J2X, ADCPIN_J2Y, 45, 45, 1900, 1900);

  control_init();

}

void sterowanieManualne(){
  // Aktualizacja sterowania -> odczyt zadanej prędkości
  joystick_update(&J1);
  joystick_update(&J2);

  control_update(&J1, &J2);

}