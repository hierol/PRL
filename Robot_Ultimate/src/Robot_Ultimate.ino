#include <utilsf.h>
#include <pwm.h>
#include <joystick.h>
#include <filtry.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <dance.h>

int tryb_robota = 1;

// Inicjalizacja kątów serw
Arm currentAngle = {{0, 0, 0, 0, 0, 0}};

float zakres1 = 0.0, zakres2 = 0.0;
float zakres3 = 0.0, zakres4 = 0.0;


void setup() {

  Serial.begin(115200);
  pwm_setup();

}

void sterowanieJoystickiem(){
  // Aktualizacja sterowania -> odczyt zadanej prędkości
  joystick_pos(&zakres1, &zakres2, 0);
  joystick_pos(&zakres3, &zakres4, 1);

  // Konwersja na kąt serwa
  currentAngle.S[2] += zakres1 * 10;
  clamp_angle(&currentAngle.S[2]);
  currentAngle.S[3] += zakres2 * 10;
  clamp_angle(&currentAngle.S[3]);
  currentAngle.S[4] += zakres3 * 10;
  clamp_angle(&currentAngle.S[4]);
  currentAngle.S[5] += zakres4 * 10;
  clamp_angle(&currentAngle.S[5]);
  
  // Ustawienie serw
  servo_move(0, currentAngle.S[0]);
  servo_move(1, currentAngle.S[1]);
  servo_move(2, currentAngle.S[2]);
  servo_move(3, currentAngle.S[3]);
  servo_move(4, currentAngle.S[4]);
  servo_move(5, currentAngle.S[5]);

  delay(400);
}


void loop() {

  if (tryb_robota == 1){
    sterowanieJoystickiem();
  } else {
    dance();
  }

}