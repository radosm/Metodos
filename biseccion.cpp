#include "iostream"
#include "math.h"
#include "cassert"

using namespace std;

double posicion(double t, double v, double h, double m, double cr){
  double a;
  double e=2.71828183;
  double g=9.81;
  a=cr/m;
  return h+ v/a + g/(a*a) - (g/a)*t - ( v/a + g/(a*a) ) * pow(e,-a*t) ;
}

double velocidad(double t, double v, double m, double cr){
  double a;
  double e=2.71828183;
  double g=9.81;
  a=cr/m;
  return -g/a + (v+g/a)*pow(e,-a*t);
}


int main(){

  double v, h, m, cr, fr, t, pos, mitad, a, t1, t2, v0, v1;
  int iter;

  cout << "Ingrese un tiempo b para el intervalo [0,b]\n";
  cin >> t;
  cout << "Ingrese una altura\n";
  cin >> h;
  cout << "Ingrese la velocidad inical\n";
  cin >> v;
  //cout << endl;
  cout << "Ingrese masa\n";
  cin >> m;
  cout << "Ingrese coeficiente de rozamiento\n";
  cin >> cr;
  cout << "Ingrese factor de restitucion\n";
  cin >> fr;
  
  v0 = v;
  assert(posicion(t,v0,h,m,cr) < 0);

  a = 0;
  iter = 0;
  while( t - a > 0.0000001 and iter < 1000 ){
    mitad = (t + a) / 2;
//    cout << "Mitad" << mitad << "\n";
    pos = posicion(mitad,v0,h,m,cr);
    if ( pos < 0 ){
      t = mitad;
    }else{
      a = mitad;
    }
    iter++;
  }

  t1=mitad;
  cout << "Se tarda " << t1 << " segundos para el primer impacto\n" << "Se realizo en " << iter << " iteraciones\n";
    
// velocidad(double t, double v, double m, double cr){

  v1=-fr*velocidad(t1, v0, m, cr);


  t=t1*10;
  a=0;
  iter=0;

  assert(posicion(t,v1,0,m,cr) < 0);

  while( t - a > 0.0000001 and iter < 1000 ){
    mitad = (t + a) / 2;
//    cout << "Mitad" << mitad << "\n";
    pos = posicion(mitad,v1,0,m,cr);
    if ( pos < 0 ){
      t = mitad;
    }else{
      a = mitad;
    }
    iter++;
  }

  t2=mitad;
  cout << "Se tarda " << t2+t1 << " segundos para el segundo impacto\n" << "Se realizo en " << iter << " iteraciones\n";

}
