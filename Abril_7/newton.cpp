#include "iostream"
#include "math.h"
#include "cassert"
#include "TFloat.h"
#include <stdlib.h>
#include <stdio.h>

using namespace std;


size_t pr;
TFloat tolerancia;
int max_iter;
TFloat g;

struct Datos{

    Datos(){}

    TFloat v0; //velocidad inicial
    TFloat h; //altura
    TFloat m; //masa
    TFloat cr; // coeficiente de rozamiento
    TFloat fr; // factor de restitucion
};

// version caida libre

TFloat posicionCaidaLibre(const Datos& d, TFloat t){
  return d.h + d.v0*t - (g/2)*t*t;
}

TFloat velocidadCaidaLibre(const Datos& d, TFloat t){
  return d.v0 - g*t;
}

TFloat aceleracionCaidaLibre(const Datos& d, TFloat t){
  TFloat menos_uno_tf=TFloat(-1,pr);
  return  menos_uno_tf*g;
}

// version con rozamiento

TFloat posicionConRozamiento(const Datos& d, TFloat t){
  TFloat a=d.cr/d.m;
  TFloat menos_uno_tf=TFloat(-1,pr);
  return d.h + d.v0/a + g/(a*a) - (g/a)*t - ( d.v0/a + g/(a*a) ) * ((menos_uno_tf*a*t).exponencial());
}

TFloat velocidadConRozamiento(const Datos& d, TFloat t){
  TFloat a=d.cr/d.m;
  TFloat menos_uno_tf=TFloat(-1,pr);
  return menos_uno_tf*g/a + (d.v0+g/a) * ((menos_uno_tf*a*t).exponencial());
}

TFloat aceleracionConRozamiento(const Datos& d, TFloat t){
  TFloat a=d.cr/d.m;
  TFloat menos_uno_tf=TFloat(-1,pr);
  return (d.v0+g/a) * ((menos_uno_tf*a*t).exponencial())*menos_uno_tf*a;
}

// genericos

// velocidad en el instante t
TFloat velocidad(const Datos& d, TFloat t){
    if (d.cr.dbl()>0){
        return velocidadConRozamiento(d, t);
    } else {
        return velocidadCaidaLibre(d, t);
    }
}

// altura en el instante t
TFloat posicion(const Datos& d, TFloat t){
    if (d.cr.dbl()>0){
        return posicionConRozamiento(d, t);
    } else {
        return posicionCaidaLibre(d, t);
    }
}

// aceleracion en el instante t
TFloat aceleracion(const Datos& d, TFloat t){
    if (d.cr.dbl()>0){
        return aceleracionConRozamiento(d, t);
    } else {
        return aceleracionCaidaLibre(d, t);
    }
}

// energia mecanica
TFloat energiaMecanica(const Datos& d, TFloat t){
  TFloat dos_tf=TFloat(2.0,pr);
  return posicion(d, t)*g + velocidad(d,t)*velocidad(d,t) / dos_tf;
}

TFloat biseccion(const Datos& d, int iteraciones){
  int iter=0;
  TFloat a=TFloat(0.0,pr);
  TFloat dos_tf=TFloat(2.0,pr);

  //busco un valor b para el intervalo [a,b] de bisección
  TFloat b = TFloat(1.0,pr);
  while (posicion(d, b).dbl()>=0){
      b=dos_tf*b;
  }

  assert(posicion(d, a).dbl()>=0);
  assert(posicion(d, b).dbl()<0);

  while( iter < iteraciones ){
    TFloat mitad = (b + a) / dos_tf;
    TFloat pos = posicion(d, mitad);
    if ( pos.dbl() < 0.0 ){
      b = mitad;
    }else{
      a = mitad;
    }
    iter++;
  }
  return (a + b) / dos_tf;
}

TFloat biseccion_velocidad(const Datos& d, int iteraciones){
  int iter=0;
  TFloat a=TFloat(0.0,pr);
  TFloat dos_tf=TFloat(2.0,pr);

  //busco un valor b para el intervalo [a,b] de bisección
  TFloat b = TFloat(1.0,pr);
  while (velocidad(d, b).dbl()>=0){
      b=dos_tf*b;
  }

  assert(velocidad(d, a).dbl()>=0);
  assert(velocidad(d, b).dbl()<0);

  while( iter < iteraciones ){
    TFloat mitad = (b + a) / dos_tf;
    TFloat pos = velocidad(d, mitad);
    if ( pos.dbl() < 0.0 ){
      b = mitad;
    }else{
      a = mitad;
    }
    iter++;
  }
  return (a + b) / dos_tf;
}


TFloat errorRelativo(TFloat a, TFloat b) {
    if (a.dbl() > b.dbl()){
      return (a - b) / b;
    } else {
      return (b - a) / b;
    }
}


TFloat newton(const Datos& d, TFloat t, int& iter){

  iter=1;

  TFloat x0 = t - posicion(d, t) / velocidad(d, t);
  TFloat x1 = x0 - posicion(d, x0) / velocidad(d, x0);

  while(errorRelativo(x0,x1).dbl() > tolerancia.dbl() && iter < max_iter){
    x0 = x1;
    x1 = x0 - posicion(d, x0) / velocidad(d, x0);
    iter++;
  }

  return x1;
}

TFloat newton_velocidad(const Datos& d, TFloat t, int& iter){

  iter=1;

  TFloat x0 = t - velocidad(d, t) / aceleracion(d, t);
  TFloat x1 = x0 - velocidad(d, x0) / aceleracion(d, x0);


//  printf("ER=%10.20f X0=%10.20f X1=%10.20f velocidad(d,t)=%10.20f velocidad(d,x0)=%10.20f\n",\
//             errorRelativo(x0,x1).dbl(),x0.dbl(),x1.dbl(),velocidad(d, t).dbl(),velocidad(d, x0).dbl());

  while(errorRelativo(x0,x1).dbl() > tolerancia.dbl() && iter < max_iter){
    x0 = x1;
    x1 = x0 - velocidad(d, x0) / aceleracion(d, x0);
    iter++;
  }

  return x1;
}


// calcula el tiempo hasta el proximo impacto
// actualiza la velocidad y la altura
TFloat proximoImpacto(Datos& d,TFloat t,int& iter){
  TFloat t1 = newton(d,t,iter);
  TFloat menos_uno_tf=TFloat(-1,pr);
  d.v0=menos_uno_tf*d.fr*velocidad(d,t1);
  d.h=TFloat(0.0,pr); // la altura despues del impacto es cero
  return t1;
}


int main(int argc, char* argv[]){

  Datos datos;
  int iter1,iter2,iter3;

  if (argc<8) {
    cerr << "Error, ingrese parametros: precision, tolerancia, max_iter, altura inicial, velocidad inicial, masa, coeficiente de rozamiento, factor de restitucion\n"; 
    exit(1);
  }
  
  pr=(size_t)atoi(argv[1]);
  assert (pr>=1 && pr <=52);
  
  g = TFloat(9.81,pr);

  tolerancia=TFloat(atof(argv[2]),pr);
  max_iter=atoi(argv[3]);
  datos.h=TFloat(atof(argv[4]),pr);
  datos.v0=TFloat(atof(argv[5]),pr);
  datos.m=TFloat(atof(argv[6]),pr);
  datos.cr=TFloat(atof(argv[7]),pr);
  datos.fr=TFloat(atof(argv[8]),pr);

  TFloat t1=biseccion(datos,1);
  t1=proximoImpacto(datos, t1, iter1);

  TFloat t_h_max=biseccion_velocidad(datos,1);
  t_h_max=newton_velocidad(datos, t_h_max, iter2);
  TFloat h_max=posicion(datos,t_h_max);

  TFloat t2=biseccion(datos,1);
  t2=proximoImpacto(datos,t2,iter3);

  printf("%d %10.20f %d %10.20f %d %10.20f %d %10.20f %d\n",pr,tolerancia.dbl(),max_iter,t1.dbl(),iter1,h_max.dbl(),iter2,(t1+t2).dbl(),iter3);

  return 0;
}
