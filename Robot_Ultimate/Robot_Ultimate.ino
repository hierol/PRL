#include <utilsf.h>
#include <pwm.h>
#include <joystick.h>
#include <filtry.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <dance.h>
#include <toolsteer.h>

int tryb_robota = 1;

// Inicjalizacja kątów serw
Arm currentAngle = {{0, 0, 0, 0, 0, 0}};

float zakres1 = 0.0, zakres2 = 0.0;
float zakres3 = 0.0, zakres4 = 0.0;


void setup() {

  Serial.begin(115200);
  pwm_setup();
  dance_setup();

}

void sterowanieManualne(){
  // Aktualizacja sterowania -> odczyt zadanej prędkości
  joystick_pos(&zakres1, &zakres2, 0);
  joystick_pos(&zakres3, &zakres4, 1);

  // Konwersja na kąt serwa
  currentAngle.S[0] += jaw_direction() * 30;  //todo: zmienic zasady clampowania
  currentAngle.S[1] += head_direction() * 10; //todo: zmienic zasady clampowania
  currentAngle.S[2] += zakres1 * 10;
  currentAngle.S[3] += zakres2 * 10;
  currentAngle.S[4] += zakres3 * 10;
  currentAngle.S[5] += zakres4 * 10;

  
  // Ustawienie serw
  for (int i = 0; i < 6; i++) {
    servo_move(i, currentAngle.S[i]);
  }


  delay(400);
}


void loop() {

  if (danceMode() == 1){
    sterowanieManualne();
  } else {
    dance();
  }

}