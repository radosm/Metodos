#include "TFloat.h"
#include "fisica.h"
#include "assert.h"
#include <iostream>
#include <stdio.h>

extern size_t pr;
extern TFloat g;

TFloat errorAbsoluto(TFloat x0, TFloat x1) { // Error absoluto= |x0-x1| 
    TFloat numerador=TFloat(0,pr);
  
    if (x0.dbl() > x1.dbl()){
      numerador=x0-x1;
    } else {
      numerador=x1-x0;
    }

    return numerador;
}

TFloat errorRelativo(TFloat x0, TFloat x1) { // Error relativo= |x0-x1| / |x0|
    TFloat denominador=TFloat(0,pr);
    TFloat menos_uno_tf=TFloat(-1.0,pr);

    if (x0.dbl() <0) {
      denominador=menos_uno_tf*x0;
    } else {
      denominador=x0;
    }
    return errorAbsoluto(x0,x1)/denominador;

}

TFloat biseccion_generico(TFloat (*f)(const Datos&,TFloat),const Datos& d, TFloat tolerancia, int max_iter, int iter, int& iter_hechas){

  TFloat a=TFloat(0.0,pr);
  TFloat dos_tf=TFloat(2.0,pr);
  TFloat cero_tf=TFloat(0.0,pr);
  TFloat tolAbs=TFloat(0.0000000001,pr);
  TFloat x0=TFloat(0,pr);
  TFloat x1=TFloat(0,pr);
  TFloat mitad,pos;

  //busco un valor b para el intervalo [a,b] de bisección
  TFloat b = TFloat(1.0,pr);
  while (f(d, b).dbl()>=0){
      b=dos_tf*b;
  }

  assert(f(d, a).dbl()>=0);
  assert(f(d, b).dbl()<0);

  iter_hechas=0;
  x0=dos_tf*b;
  x1=b;
  while( iter_hechas < iter ){

    // Solo se ejecuta este bloque si no es una llamada a biseccion_n
    if (iter==max_iter && errorRelativo(x0,x1).dbl() < tolerancia.dbl() && errorAbsoluto(f(d,x1),cero_tf).dbl() <= tolAbs.dbl() ) { 
      break; 
    }

    mitad = (b + a) / dos_tf;
    pos = f(d, mitad);

    if ( pos.dbl() < 0.0 ){
      b = mitad;
    }else{
      a = mitad;
    }

    x0=x1;
    x1=mitad;
    iter_hechas++;
  }
  return x1;
}

TFloat biseccion_n(TFloat (*f)(const Datos&,TFloat),const Datos& d, int iter){
  int ih;
  return biseccion_generico(f,d,0,-1,iter,ih); 
}


TFloat biseccion(TFloat (*f)(const Datos&,TFloat),const Datos& d,TFloat tolerancia, int max_iter, int& iter){
  return biseccion_generico(f,d,tolerancia,max_iter,max_iter,iter);
}

TFloat newton(TFloat (*f)(const Datos&,TFloat),TFloat (*f1)(const Datos&,TFloat),const Datos& d,TFloat tolerancia,int max_iter, TFloat t, int& iter){

  TFloat cero_tf=TFloat(0.0,pr);
  TFloat tolAbs=TFloat(0.0000000001,pr);
  TFloat x0 = t ;
  TFloat x1 = x0 - f(d, x0) / f1(d, x0);  // 1ra iteracion

  iter=1;
  while((errorRelativo(x0,x1).dbl() > tolerancia.dbl() || errorAbsoluto(f(d,x1),cero_tf).dbl() > tolAbs.dbl()) && iter < max_iter){
    x0 = x1;
    x1 = x0 - f(d, x0) / f1(d, x0);
    iter++;
  }

  return x1;
}

