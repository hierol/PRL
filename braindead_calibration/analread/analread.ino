#ifndef analread_h
#define analread_h

extern float zakres1 = 0.0;
extern float zakres2 = 0.0;

#endif
//Potentiometer is connected at analog pin 0:
int analogPin1 = A6;
int analogPin2 = A7;
int val1 = 0;
int val2 = 0;
int drift=100;
//variable to store the value read
void setup () 
{
 Serial.begin (9600);
//Setup serial
}

void loop () 
{
  // Odczyt
  val1 = analogRead (analogPin1);
  val2 = analogRead (analogPin2);

  // Wstępne przesunięcie
  val1 -= 1900;
  val2 -= 1900;

  // Zerowanie driftu
  if (( val1 >= (-1*drift) ) && ( val1 <= drift )) {val1=0;}
  if (( val2 >= (-1*drift) ) && ( val2 <= drift )) {val2=0;}

  // Skalowanie
  if (val1 < 0) {
    val1 += drift;
    zakres1 = val1 / (1900.0 - drift);
  } else if (val1 > 0) {
    val1 += drift;
    zakres1 = val1 / (2100.0 + drift);
  } else {zakres1 = 0;}

  if (val2 < 0) {
    val2 += drift;
    zakres2 = val2 / (1900.0 - drift);
  } else if (val2 > 0) {
    val2 += drift;
    zakres2 = val2 / (2100.0 + drift);
  } else {zakres2 = 0;}


  //Serial.println("+================+");
  Serial.print("kanał 1 => sterowanie: "); Serial.print(zakres1); Serial.print(" | Anal: "); Serial.println(val1);
  Serial.print("kanał 2 => sterowanie: "); Serial.print(zakres2); Serial.print(" | Anal: "); Serial.println(val2);
  Serial.println("+================+");
  delay(1000);
}