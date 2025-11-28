#include <math.h>


double maptorad(double deg) {
  return deg*M_PI/180;
}

double maptodeg(double rad) {
  return rad*180/M_PI;
}

void setup() {

  Serial.begin(115200);

  //const double pi = 3.14159;

  //wspolzedne konca narzedzia
  const double j = 5; 
  const double k = 3;

  //kat narzedzia i dlugosci segmentow
  const double a = 10;// * (M_PI/180);
  const double L1 = 5;
  const double L2 = 3;
  const double L3 = 2;

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

  Serial.printf(" m: %f \n n: %f \n t112: %f \n l: %f \n t13: %f \n p1: %f \n p2: %f \n t2: %f \n p3: %f \n o: %f \n p: %f \n ",m,n,t112,l,t13,p1,p2,t2,p3,o,p);


  double k1 = maptodeg( atan( p/o ) );
  double k2 = p2;
  double elprimo = sqrt( (j-o)*(j-o) + (k-p)*(k-p) );
    Serial.printf("elprimo: %f \n" , elprimo );
  double k3 = acos(( L2*L2 + L1*L1 - elprimo*elprimo ) / ( 2*L2*L1 )); // wynik w rad

    Serial.println( maptodeg( k3 ));

  Serial.println( k1 );

  // Serial.printf("\n w stopniach: \n p1: %f \n p2: %f \n p3: %f \n", maptodeg(p1) , maptodeg(p2) , maptodeg(p3) );
}

void loop() {
  // put your main code here, to run repeatedly:

}
