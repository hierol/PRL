#include "utilsf.h"
#include "pwm.h"
#include "filtry.h"
#include "joystick.h"
#include "control.h"
#include <Arduino.h>


LPFI_data LPF_J1X, LPF_J1Y;
LPFI_data LPF_J2X, LPF_J2Y;

//LPFI_data LPF_B1, LPF_B2; // Pary przycisków lewo-prawo

AngleAcc AngleS0, AngleS1, AngleS2, AngleS3; // Instancje kątów serw // 4 Serwa Pierwotne

AngleAcc AngleS4, AngleS5; // Dwa Serwa Ostateczne // S5->Chwytak


static const float si = 0.3f; // small input -> część sterowania która pomija filtr [zakres od 0.0 do 1.0]
static const float T = 0.5f; // okres wywołania [sekundy]


// Wstępna deklaracja
static void angle_init(AngleAcc* angleAcc, float start_angle, float Ki);
static void angle_update(float x, AngleAcc* angleAcc);
static float filterI(float x, LPFI_data* lpfi_data);
static float filterII(float x, LPFII_data* lpfii_data);
static unsigned char braking(float x_n, float x_n_1);
static void servo_update();


void control_init() {
  // Inicjalizacja instancji filtrów LPFI <-------------------------------------------------------- USTAWIĆ TAU
  LPFI_init(&LPF_J1X, 1.0f, 1.0f); // Instancja LPF // stała czasowa // wzmocnienie
  LPFI_init(&LPF_J1Y, 1.0f, 1.0f);
  LPFI_init(&LPF_J2X, 1.0f, 1.0f);
  LPFI_init(&LPF_J2Y, 1.0f, 1.0f);

  // TO DO
  //LPFI_init(&LPF_B1, tau, 1.0f); // SerwoX na przyciski
  //LPFI_init(&LPF_B2, tau, 1.0f); // Chwytak


  // Inicjalizacja kątów i wzmocnienia całki (Ki) poszczególnych serw
  angle_init(&AngleS0, START_ANGLE_S0, 10.0f); // Instancja całki kąta // kąt początkowy // wzmocnienie całki
  angle_init(&AngleS1, START_ANGLE_S1, 10.0f);
  angle_init(&AngleS2, START_ANGLE_S2, 10.0f);
  angle_init(&AngleS3, START_ANGLE_S3, 10.0f);

  // TO DO
  angle_init(&AngleS4, START_ANGLE_S4, 10.0f); // SerwoX na przyciski
  angle_init(&AngleS5, START_ANGLE_S5, 10.0f); // Chwytak


  // Ustawienie serw na zinicjalizowaną pozycję
  servo_update();


  // Opóźnienie wywołania
  delay((int)(T*1000)); // T=0.01 -> delay=10ms
}


void control_update(Joystick* joy1, Joystick* joy2) {

  // Filtracja Dolnoprzepustowa // "Ładowanie" sterowania
  // Joystick 1 oś X
  float J1X_f = filterI(joy1->x*(1.0f-si), &LPF_J1X) + si*joy1->x;
  // Joystick 1 oś Y
  float J1Y_f = filterI(joy1->y*(1.0f-si), &LPF_J1Y) + si*joy1->y;
  // Joystick 2 oś X
  float J2X_f = filterI(joy2->x*(1.0f-si), &LPF_J2X) + si*joy2->x;
  // Joystick 2 oś Y
  float J2Y_f = filterI(joy2->y*(1.0f-si), &LPF_J2Y) + si*joy2->y;

  // TO DO - dodać Buttons* buttons do argumentów funkcji
  //float B1_f = filterI(buttons->b1*(1.0f-si), &LPF_B1) + si*buttons->b1;
  //float B2_f = filterI(buttons->b2*(1.0f-si), &LPF_B2) + si*buttons->b2;


  // PRZYPISAĆ KANAŁY JOYSTICKA I PAR PRZYCISKÓW DO SERW <-------------------------------------------- TO DO
  angle_update(J1X_f, &AngleS0); // całka obecnej próbki
  angle_update(J1Y_f, &AngleS1);
  angle_update(J2X_f, &AngleS2);
  angle_update(J2Y_f, &AngleS3);

  //angle_update(B1_f, &AngleS);
  //angle_update(B2_f, &AngleS);


  // Aktualizacja stanu serw
  servo_update();


  // Opóźnienie wywołania
  delay((int)(T*1000)); // T=0.01 -> delay=10ms
}


static void angle_init(AngleAcc* angleAcc, float start_angle, float Ki) {
  angleAcc->accumulator = start_angle; // początkowy dokładny kąt
  angleAcc->angle = (int)start_angle; // początkowy kąt całkowity
  angleAcc->Ki = Ki; // wzmocnienie całki
  float _ = timeDelta(&angleAcc->lastTime); // offset lastTime -> minimalizacja "uderzenia" całki
}

static void angle_update(float x, AngleAcc* angleAcc) {
  float Tp = timeDelta(&angleAcc->lastTime); // pomiar okresu wywołania całki
  float new_accumulator = Tp*angleAcc->Ki*x + angleAcc->accumulator; // integrator
  if (new_accumulator > ANGLE_MAX) { new_accumulator = ANGLE_MAX; } // ogranicz do +90.0
  else if (new_accumulator < ANGLE_MIN) { new_accumulator = ANGLE_MIN; } // ogranicz do -90.0
  angleAcc->accumulator = new_accumulator; // nadpisanie kątów
  angleAcc->angle = (int)new_accumulator;
}


static float filterI(float x, LPFI_data* lpfi_data) {
  if (SMOOTHING==OFF) {return x;} // Jeśli wygładzanie jest wyłączone -> omiń filtr

  // Przy szybkim hamowaniu doprowadź do stanu ustalonego mniejszej wartości
  if ( FAST_BRAKE==ON && braking(x, lpfi_data->y_n_1) ) {
    lpfi_data->y_n_1 = x; // symulowanie stanu ustalonego
    float _ = timeDelta(&lpfi_data->lastTime); // symulowanie wywołania filtra
    return x; // zwróć wartość "hamującą"
  } else {
    return LPF_I(x, lpfi_data); // normalna praca filtra
  }
}

static float filterII(float x, LPFII_data* lpfii_data) {
  if (SMOOTHING==OFF) {return x;}

  if ( FAST_BRAKE==ON && braking(x, lpfii_data->y_n_1) ) {
    lpfii_data->y_n_1 = x;
    lpfii_data->y_n_2 = x;
    float _ = timeDelta(&lpfii_data->lastTime);
    return x;
  } else {
    return LPF_II(x, lpfii_data);
  }
}


static unsigned char braking(float x_n, float x_n_1) {
  // Jeśli |x(n)| < |x(n-1)| to hamowanie=prawda
  if (ABS(x_n) < ABS(x_n_1)) {
    return 1; // Prawda
  } else {
    return 0; // Fałsz
  }
}


static void servo_update() {
  // Ustawienie serw
  servo_move(0, AngleS0.angle);
  servo_move(1, AngleS1.angle);
  servo_move(2, AngleS2.angle);
  servo_move(3, AngleS3.angle);
  servo_move(4, AngleS4.angle);
  servo_move(5, AngleS5.angle);
}


void reset_lastTime() {
  unsigned long now = millis();
  LPF_J1X.lastTime = now; LPF_J1Y.lastTime = now;
  LPF_J2X.lastTime = now; LPF_J2Y.lastTime = now;

  AngleS0.lastTime = now; AngleS1.lastTime = now; AngleS2.lastTime = now; AngleS3.lastTime = now;
  AngleS4.lastTime = now; AngleS5.lastTime = now;
}


static void angle_overwrite(AngleAcc* angleAcc, int newAngle) {
  angleAcc->accumulator = (float)newAngle;
  angleAcc->angle = newAngle;
}


void dance_angle_overwrite(int angles[6]) {
  angle_overwrite(&AngleS0, angles[0]);
  angle_overwrite(&AngleS1, angles[1]);
  angle_overwrite(&AngleS2, angles[2]);
  angle_overwrite(&AngleS3, angles[3]);
  angle_overwrite(&AngleS4, angles[4]);
  angle_overwrite(&AngleS5, angles[5]);
}
