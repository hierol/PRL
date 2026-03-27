#include "toolsteer.h"
#include <Arduino.h>
#include "board.h"

void toolsteer_setup() {

    pinMode(LeftBumper, INPUT_PULLUP);
    pinMode(RightBumper, INPUT_PULLUP);

    pinMode(LeftJoystick, INPUT_PULLUP);
    pinMode(RightJoystick, INPUT_PULLUP);

    pinMode(DANCE_MODE_PIN, INPUT_PULLUP);

}

int head_direction() {
    int buttonState1 = digitalRead(LeftBumper);
    int buttonState2 = digitalRead(RightBumper);
    
    if (buttonState1 == LOW && buttonState2 == LOW) {
        return 0;
    }

    if (buttonState1 == LOW) {
        return -1;
    }
    
    if (buttonState2 == LOW) {
        return 1;
    }

    return 0;
}

int jaw_direction() {
    int buttonState1 = digitalRead(LeftJoystick);
    int buttonState2 = digitalRead(RightJoystick);
    Serial.print("Jaw button state: "); Serial.print(buttonState1); Serial.print(", "); Serial.println(buttonState2);
    
    if (buttonState1 == LOW && buttonState2 == LOW) {
        return 0;
    }

    if (buttonState1 == LOW) {
        return -1;
    }
    
    if (buttonState2 == LOW) {
        return 1;
    }

    return 0;
}