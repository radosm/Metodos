#include "TFloat.h"
#include "fisica.h"
#include "assert.h"

extern size_t pr;
extern TFloat tolerancia;
extern int max_iter;
extern TFloat g;


TFloat errorRelativo(TFloat a, TFloat b) {
    if (a.dbl() > b.dbl()){
      return (a - b) / b;
    } else {
      return (b - a) / b;
    }
}

TFloat biseccion_n(TFloat (*f)(const Datos&,TFloat),const Datos& d, int iter,int& iter_hechas){

  TFloat a=TFloat(0.0,pr);
  TFloat dos_tf=TFloat(2.0,pr);

  //busco un valor b para el intervalo [a,b] de bisección
  TFloat b = TFloat(1.0,pr);
  while (f(d, b).dbl()>=0){
      b=dos_tf*b;
  }

  assert(f(d, a).dbl()>=0);
  assert(f(d, b).dbl()<0);

  iter_hechas=0;
  while( iter_hechas < iter ){
    if (iter==max_iter && errorRelativo(a,b).dbl() < tolerancia.dbl()) break;  // Solo sale por error relativo si es una llamada comun
    TFloat mitad = (b + a) / dos_tf;
    TFloat pos = f(d, mitad);
    if ( pos.dbl() < 0.0 ){
      b = mitad;
    }else{
      a = mitad;
    }
    iter_hechas++;
  }
  return (a + b) / dos_tf;
}

TFloat biseccion_n(TFloat (*f)(const Datos&,TFloat),const Datos& d, int iter){
  int ih;
  return biseccion_n(f,d,iter,ih);
}


TFloat biseccion(TFloat (*f)(const Datos&,TFloat),const Datos& d, int& iter){
  return biseccion_n(f,d,max_iter,iter);
}

TFloat newton(TFloat (*f)(const Datos&,TFloat),TFloat (*f1)(const Datos&,TFloat),const Datos& d, TFloat t, int& iter){

  iter=1;

  TFloat x0 = t ;
  TFloat x1 = x0 - f(d, x0) / f1(d, x0);

  while(errorRelativo(x0,x1).dbl() > tolerancia.dbl() && iter < max_iter){
    x0 = x1;
    x1 = x0 - f(d, x0) / f1(d, x0);
    iter++;
  }

  return x1;
}

