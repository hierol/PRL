#include <math.h>


struct position {
  int x, y, z; // z to wysokosc a nie y xd
} Position;

struct Position positioner(double x, double y, double z);

double maptorad(double deg) {
  return deg*M_PI/180;
}

double maptodeg(double rad) {
  return rad*180/M_PI;
}

void setup() {

  Serial.begin(115200);

  // Serial.printf("\n w stopniach: \n p1: %f \n p2: %f \n p3: %f \n", maptodeg(p1) , maptodeg(p2) , maptodeg(p3) );
}

void loop() {
  // put your main code here, to run repeatedly:

}



struct Position positioner(double x, double y, double z) {
  
  //dlugosci segmentow
  const double l1 = 10;
  const double l2 = 10;
  const double l3 = 20;

  

  double k0 = atan( y)



  return position;
}