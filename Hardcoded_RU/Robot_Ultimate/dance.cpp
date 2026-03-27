#include "dance.h"
#include <Arduino.h>
#include <utilsf.h>
#include <pwm.h>

int dancepos;

Arm dancesequence[] = {
    {{0, 0, 0, 0, 0, 0}},
    {{30, 30, 30, 30, 30, 30}},
    {{-30, -30, -30, -30, -30, -30}},
    {{15, -15, 15, -15, 15, -15}},
    {{-15, 15, -15, 15, -15, 15}},
    {{45, 45, 45, 45, 45, 45}},
    {{-45, -45, -45, -45, -45, -45}},
    {{20, -20, 20, -20, 20, -20}},
    {{-20, 20, -20, 20, -20, 20}},
    {{0, 0, 0, 0, 0, 0}}
};


void dance_setup() {

    pinMode(DANCE_MODE_PIN, INPUT_PULLUP);

}


bool danceMode_1() {
    
    int buttonState = digitalRead(PIN);
    //Serial.print("Button state: "); Serial.println(buttonState);
    
    if (buttonState == LOW) {
        return true;
    } else {
        return false;
    }
}


void dance() {
    for(dance_pos = 0; dance_pos < (sizeof(dancesequence)/sizeof(Arm)); dance_pos++) {

        for (int servo_number = 0; servo_number < 6; servo_number++) {
            servo_move(servo_number, dancesequence[dance_pos].S[servo_number]);
            Serial.print("Servo "); Serial.print(servo_number); Serial.print(": "); Serial.println(dancesequence[dance_pos].S[servo_number]);
        }

        delay(500);
    }
}

Arm dance_getCurrentPos() {
    return dancesequence[dancepos];
}