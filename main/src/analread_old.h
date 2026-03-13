#ifndef analread_h
#define analread_h

float zakres0 = 0.0;
float zakres1 = 0.0;
float zakres2 = 0.0;
float zakres3 = 0.0;

extern float war_s0 = 0; //todo
extern float war_s1 = 0;
extern float war_s2 = 0;
extern float war_s3 = 0; //todo

#endif
//Potentiometer is connected at analog pin 0:
int analogPin1 = A6;
int analogPin2 = A7;
int val1 = 0;
int val2 = 0;
int drift=100;
//variable to store the value read
void asetup() 
{
 //Serial.begin (9600);
//Setup serial
}

void joystick_pos() 
{
  // Odczyt
  val1 = analogRead (analogPin1); // 0.0-3.3V ~ 0-4095 ~ 0-3800
  val2 = analogRead (analogPin2);

  int og_val1 = val1;
  int og_val2 = val2;

  // Wstępne przesunięcie - pozycja środkowa joysticka = 0
  val1 -= 1915; // 1900-1927 // og 1900 // zakres lewo 1915-drift // prawo 2180-drift
  val2 -= 1870; // 1860-1883 // og 1900 // zakres lewo 1870-drift // prawo 2225-drift

  // Zerowanie driftu - Strefa Nieczułości -> +-100
  if (( val1 >= (-1*drift) ) && ( val1 <= drift )) {val1=0;}
  if (( val2 >= (-1*drift) ) && ( val2 <= drift )) {val2=0;}

  // Skalowanie - Normalizacja do +-1.0
  if (val1 < 0) {
    val1 += drift;
    zakres1 = val1 / (1915.0 - drift);
  } else if (val1 > 0) {
    val1 -= drift;
    zakres1 = val1 / (2180.0 - drift);
  } else {zakres1 = 0;}

  if (val2 < 0) {
    val2 += drift;
    zakres2 = val2 / (1870.0 - drift);
  } else if (val2 > 0) {
    val2 -= drift;
    zakres2 = val2 / (2225.0 - drift);
  } else {zakres2 = 0;}

  //if (zakres1 > 1){
  //  zakres1 = 1;
  //}
  //if (zakres2 > 1){
  //  zakres2 = 1;
  //}

  //war_s0 = 270 * zakres0 + 380; // to implement
  war_s1 = 270 * zakres1 + 380;
  war_s2 = 270 * zakres2 + 380;
  //war_s3 = 270 * zakres3 + 380; // to implement

  //Serial.println("+================+");
  Serial.print("kanał 1 => sterowanie: "); Serial.print(zakres1); Serial.print(" | Anal: "); Serial.print(val1); \
  Serial.print(" | Anal_OG: "); Serial.println(og_val1);
  Serial.print("kanał 2 => sterowanie: "); Serial.print(zakres2); Serial.print(" | Anal: "); Serial.print(val2); \
  Serial.print(" | Anal_OG: "); Serial.println(og_val2);
  Serial.println("+================+");
  delay(200);
}