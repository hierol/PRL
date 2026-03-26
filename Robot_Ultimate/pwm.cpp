 #include <filtry.h>
 // Definicja pinów
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

void setup() {
  // Ustawienie pinów jako wyjścia
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Przykład: Płynne przejście kolorów
  setColor(255, 0, 0);  // Czerwony
  delay(1000);
  setColor(0, 255, 0);  // Zielony
  delay(1000);
  setColor(0, 0, 255);  // Niebieski
  delay(1000);
  setColor(255, 255, 0);  // Żółty
  delay(1000);
  setColor(80, 0, 80);  // Fioletowy
  delay(1000);
  setColor(255, 255, 255);  // Biały
  delay(1000);
}

// Funkcja pomocnicza do ustawiania koloru
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}