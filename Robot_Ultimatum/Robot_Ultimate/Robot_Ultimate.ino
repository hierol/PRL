#include "utilsf.h"
#include "board.h"
#include "pwm.h"
#include "joystick.h"
#include "control.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "dance.h"
#include "toolsteer.h"

int tryb_robota = 1;

// Instancje joysticka
Joystick J1;
Joystick J2;


void setup() {

  Serial.begin(115200);
  pwm_setup();
  dance_setup();

  joystick_init(&J1, ADCPIN_J1X, ADCPIN_J1Y, 80, 80, 1916, 1872, 0, 0); // (*joystick, jx_pin, jy_pin, driftX, driftY, jx_center, jy_center, inv_x, inv_y)
  joystick_init(&J2, ADCPIN_J2X, ADCPIN_J2Y, 80, 80, 1883, 1845, 0, 1);
  toolsteer_setup();

  control_init();

}

bool danceMode() {
  
  if (digitalRead(DANCE_MODE_PIN) == LOW) {

    Serial.println("Dance mode ON");
    return 1;

  } else {

    Serial.println("Dance mode OFF");
    return 0;

  }
}

void loop(){
  // Aktualizacja sterowania -> odczyt zadanej prędkości

  if (danceMode() == 1){

    dance();

    Arm temp = dance_getCurrentPos();
    dance_angle_overwrite(temp.S);
    reset_lastTime();
    
  } else {

  joystick_update(&J1);
  joystick_update(&J2);

  control_update(&J1, &J2);
  }

}