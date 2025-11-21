#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Ustawienia Wi-Fi AP
const char* ssid = "ESP32_SERVO_AP";
const char* password = "12345678"; // Hasło musi mieć min. 8 znaków

// Ustawienia PCA9685
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN 114  // Minimalna szerokość impulsu
#define SERVOMAX 644  // Maksymalna szerokość impulsu
#define SERVO_FREQ 50 // Częstotliwość dla serw

// Kanały PCA9685 dla 6 serw
#define SERVO1_CHANNEL 0
#define SERVO2_CHANNEL 1
#define SERVO3_CHANNEL 2
#define SERVO4_CHANNEL 3
#define SERVO5_CHANNEL 4
#define SERVO6_CHANNEL 5


WebServer server(80);

// Funkcja pomocnicza do ustawiania kąta serwa
void setServoAngle(uint8_t servo_num, int angle) {
  int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(servo_num, 0, pulse);
}

// Obsługa żądania głównej strony
void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Kontrola Serw ESP32 & PCA9685</title>
<style>
  body{text-align: center; font-family: sans-serif;}
  h2{color: #333;}
  .slider-container{margin: 20px auto; width: 80%; max-width: 400px; padding: 10px; border: 1px solid #ccc; border-radius: 5px;}
  input[type=range]{width: 100%;}
  .angle-display{font-weight: bold; margin-top: 10px;}
</style>
</head>
<body>
  <h2>Sterowanie 6 Serwomechanizmami</h2>

  <div class="slider-container">
    <h3>Serwo 1 (Kanał 0)</h3>
    <input type="range" min="10" max="80" value="30" class="slider" id="servo1Range" onchange="sendServoData(0, this.value)">
    <p>Kąt: <span id="servo1Angle" class="angle-display">30</span>°</p>
  </div>

  <div class="slider-container">
    <h3>Serwo 2 (Kanał 1)</h3>
    <input type="range" min="0" max="180" value="90" class="slider" id="servo2Range" onchange="sendServoData(1, this.value)">
    <p>Kąt: <span id="servo2Angle" class="angle-display">90</span>°</p>
  </div>

  <div class="slider-container">
    <h3>Serwo 3 (Kanał 2)</h3>
    <input type="range" min="0" max="180" value="180" class="slider" id="servo3Range" onchange="sendServoData(2, this.value)">
    <p>Kąt: <span id="servo3Angle" class="angle-display">180</span>°</p>
  </div>

  <div class="slider-container">
    <h3>Serwo 4 (Kanał 3)</h3>
    <input type="range" min="0" max="180" value="30" class="slider" id="servo4Range" onchange="sendServoData(3, this.value)">
    <p>Kąt: <span id="servo4Angle" class="angle-display">30</span>°</p>
  </div>

  <div class="slider-container">
    <h3>Serwo 5 (Kanał 4)</h3>
    <input type="range" min="0" max="180" value="30" class="slider" id="servo5Range" onchange="sendServoData(4, this.value)">
    <p>Kąt: <span id="servo5Angle" class="angle-display">30</span>°</p>
  </div>

  <div class="slider-container">
    <h3>Serwo 6 (Kanał 5)</h3>
    <input type="range" min="0" max="180" value="90" class="slider" id="servo6Range" onchange="sendServoData(5, this.value)">
    <p>Kąt: <span id="servo6Angle" class="angle-display">90</span>°</p>
  </div>

<script>
  // Aktualizacja wyświetlanego kąta przy przesuwaniu suwaka
  document.querySelectorAll('.slider').forEach(slider => {
    slider.addEventListener('input', function() {
      document.getElementById(this.id.replace('Range', 'Angle')).textContent = this.value;
    });
  });

  // Wysyłanie danych do ESP32
  function sendServoData(servoNum, angle) {
    var xhr = new XMLHttpRequest();
    // Żądanie GET: /set?servo=X&angle=Y
    xhr.open("GET", "/set?servo=" + servoNum + "&angle=" + angle, true);
    xhr.send();
  }
</script>
</body>
</html>
)rawliteral";
  server.send(200, "text/html", html);
}

// Obsługa żądania ustawienia serwa (/set?servo=X&angle=Y)
void handleSetServo() {
  if (server.hasArg("servo") && server.hasArg("angle")) {
    int servo_num = server.arg("servo").toInt();
    int angle = server.arg("angle").toInt();

    if (servo_num >= 0 && servo_num <= 5 && angle >= 0 && angle <= 180) {
      Serial.printf("Ustawianie Serwa %d na kąt %d\n", servo_num + 1, angle);
      uint8_t pca_channel = (servo_num == 0) ? SERVO1_CHANNEL : 
                            (servo_num == 1) ? SERVO2_CHANNEL :
                            (servo_num == 2) ? SERVO3_CHANNEL :
                            (servo_num == 3) ? SERVO4_CHANNEL :
                            (servo_num == 4) ? SERVO5_CHANNEL : SERVO6_CHANNEL;
      setServoAngle(pca_channel, angle);
      server.send(200, "text/plain", "OK");
      return;
    }
  }
  server.send(400, "text/plain", "Błąd parametru");
}

void setup() {
  Serial.begin(115200);
  
  // 1. Inicjalizacja PCA9685
  Wire.begin(); // Opcjonalnie: Wire.begin(21, 22); dla jawnego ustawienia pinów
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Ustawienie częstotliwości PWM dla serw (50 Hz)

  // Ustawienie początkowe wszystkich serw na 90 stopni
  setServoAngle(SERVO1_CHANNEL, 30);
  setServoAngle(SERVO2_CHANNEL, 90);
  setServoAngle(SERVO3_CHANNEL, 180);
  setServoAngle(SERVO4_CHANNEL, 30);
  setServoAngle(SERVO5_CHANNEL, 30);
  setServoAngle(SERVO6_CHANNEL, 90);

  // 2. Konfiguracja Wi-Fi (Tryb Access Point)
  Serial.print("Konfiguracja punktu dostępu: ");
  Serial.println(ssid);
  WiFi.softAP(ssid, password);
  IPAddress apIP = WiFi.softAPIP();
  Serial.print("Adres IP AP: ");
  Serial.println(apIP);

  // 3. Konfiguracja Serwera Web
  server.on("/", handleRoot);
  server.on("/set", handleSetServo); // Endpoint do sterowania serwami

  server.begin();
  Serial.println("Serwer HTTP uruchomiony");
}

void loop() {
  server.handleClient();
}