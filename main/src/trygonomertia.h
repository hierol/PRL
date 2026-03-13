#include <math.h>

extern double katyO1;
extern double katyO2;
extern double katyO3;

struct angles{
  double O1;
  double O2;
  double O3;
};

struct angles trig(double xk, double yk, double p);

void tsetup() {
  
  //Serial.begin(115200);
  Serial.println("hallo");

  
  trig(7,17,0.3);
  
}

extern struct angles trig(double xk, double yk, double p){ // xk, yk - kordy narzedzia   p - nachylenie narzedzia
  struct angles katy;

  // dlugosci segmentow
  double l1 = 10;
  double l2 = 10;
  double l3 = 20;


  // kordy 4 serwa od dolu
  double xw = xk - l3*cos(p);
  double yw = yk - l3*sin(p);

  // kat 3 serwa
  double t = (pow(xw,2) + pow(yw,2) - pow(l1,2) - pow(l2,2)) / (2*l1*l2); // pomocnicza
  katy.O2 = -acos(t); // wywalic minus zeby wygiął sie w druga strone

  // kat 2 serwa
  double k1 = l1 + l2*cos(katy.O2); // pomocnicza
  double k2 = l2*sin(katy.O2); //pomocnicza
  katy.O1 = atan2(yw,xw) - atan2(k2,k1); // kat

  //kat 4 serwa
  katy.O3 = p - katy.O1 - katy.O2;

  Serial.printf (" xw: %f \n yw: %f \n t: %f \n O2: %f \n k1: %f \n k2: %f \n O1: %f \n O3: %f \n",xw,yw,t,katy.O2,k1,k2,katy.O1,katy.O3);

  double katyO1 = katy.O1;
  double katyO2 = katy.O2;
  double katyO3 = katy.O3;
}
// trygonomertryja kinda dziala, trzeba przetlumaczyc O1-O3 na wartosc ktora wyslemy do serw. proponuje wykorzystac wspolny kod z kalibracji, bo tam jest juz sterowanie za pomoca przyciskow *yay*. 