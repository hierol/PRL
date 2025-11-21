#include <math.h>


double maptorad(double deg) {
  return deg*M_PI/180;
}

void setup() {

  Serial.begin(115200);

  //const double pi = 3.14159;

  const double j = 5;
  const double k = 3;

  const double a = 10;// * (M_PI/180);
  const double L1 = 5;
  const double L2 = 3;
  const double L3 = 2;


  double m = j - L3*cos( maptorad(a) );
  double n = k - L3*sin( maptorad(a) );

  Serial.println( cos( maptorad(a) ) );
  Serial.println( a );

  double t112 = atan( maptorad(n/m) );
  double l = sqrt( m*m + n*n );
  double t13 = 1/( cos(maptorad(( L2*L2 - L1*L1 - l*l ) / ( -2*L1 ))) );

  double p1 = t112 + t13;
  double p2 = acos(maptorad(( l*l - L2*L2 - L1*L1 )/( -2*L2*L1 )));
  double t2 = p1 + p2 - 180;
  double p3 = ( 180 - t2 ) + a;

  double o = m - L2*cos( maptorad(t2) );
  double p = n - L2*sin( maptorad(t2) );

  Serial.printf(" m: %f \n n: %f \n t112: %f \n l: %f \n t13: %f \n p1: %f \n p2: %f \n t1: %f \n p2: %f \n o: %f \n p: %f \n ",m,n,t112,l,t13,p1,p2,t2,p3,o,p);

}

void loop() {
  // put your main code here, to run repeatedly:

}
