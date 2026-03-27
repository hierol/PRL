#include <Arduino.h>
#include <math.h>
#include "trig.h"
#include <pwm.h>
#include <joystick.h>

float x = 30;
float y = 12;
float Vx = 0;
float Vy = 0;

double maptorad(double deg) {
  return deg*M_PI/180;
}

double maptodeg(double rad) {
  return rad*180/M_PI;
}

void trig(int j, int k) {

  //const double pi = 3.14159;


  //kat narzedzia i dlugosci segmentow
  const double a = -10;// * (M_PI/180);
  const double L1 = 10;
  const double L2 = 10;
  const double L3 = 20;

  // wspolrzedne osi 3
  double m = j - L3*cos( maptorad(a) );
  double n = k - L3*sin( maptorad(a) );

  double t112 = atan(n/m); // wynik w rad
  double l = sqrt( m*m + n*n ); // odleglosc bazy do p3
  double t13 = acos(( L2*L2 - L1*L1 - l*l ) / ( -2*l*L1 )); // wynik w rad

  double p1 = t112 + t13; // wynik w rad
  double p2 = acos(( l*l - L2*L2 - L1*L1 )/( -2*L2*L1 )); // wynik w rad
  double t2 = p1 + p2 - M_PI; // wynik w rad
  double p3 = ( M_PI - t2 ) + maptorad(a); // wynik w rad

  double o = m - L2*cos(t2);
  double p = n - L2*sin(t2);

 //Serial.printf(" m: %f \n n: %f \n t112: %f \n l: %f \n t13: %f \n p1: %f \n p2: %f \n t2: %f \n p3: %f \n o: %f \n p: %f \n ",m,n,t112,l,t13,p1,p2,t2,p3,o,p);

  double k1 = maptodeg( atan( p/o ) );
  double k2 = p2;
  double elprimo = sqrt( (j-o)*(j-o) + (k-p)*(k-p) );
    //Serial.printf("elprimo: %f \n" , elprimo );
  double k3 = acos(( L2*L2 + L1*L1 - elprimo*elprimo ) / ( 2*L2*L1 )); // wynik w rad

    //Serial.println( maptodeg( k3 ));

  //Serial.println( k1 );

  int S1 = -maptodeg(p1)+90;
  int S2 = -maptodeg(p2)+180;
  int S3 = -maptodeg(p3)+180;
  
    servo_move(2, S1);
    servo_move(3, S2);
    servo_move(4, S3);
    Serial.println("servo 2 ustawione na: " + String(S1));
    Serial.println("servo 3 ustawione na: " + String(S2));
    Serial.println("servo 4 ustawione na: " + String(S3));
    delay(1000);
}

void absoluteSteer() {

  joystick_pos(&Vx, &Vy, 0);
  x += Vx;
  y += Vy;
  Serial.println("Vx: " + String(Vx) + " Vy: " + String(Vy));
  Serial.println("x: " + String(x) + " y: " + String(y));
  trig(x, y);

}