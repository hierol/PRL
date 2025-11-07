#include <>

Servo servo1, servo2, servo3, servo4, servo5; 



void setup() {
  // put your setup code here, to run once:
  // 3, 9, 10, 11
servo1.attach( 11 );
servo2.attach
Serial.begin(9600);
}

void loop() {
  servo1.write(180);
  delay(500);
  servo1.write(0);
  delay(500);
  Serial.println("Dziala");
//// put your main code here, to run repeatedly:
//for ( int i=0 ; i < 5000; i= i+100){
//  myservo.writeMicroseconds(i);
//  Serial.println(i);
//  delay(500);
//}
}
