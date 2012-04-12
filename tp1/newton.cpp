#include "iostream"
#include "math.h"
#include "cassert"
#include "TFloat.h"
#include <stdlib.h>
#include <stdio.h>
#include "fisica.h"
#include "metodos.h"

using namespace std;

size_t pr;
TFloat g;


// calcula el tiempo hasta el proximo impacto
// actualiza la velocidad y la altura
TFloat proximoImpacto(Datos& d,TFloat tolerancia, int max_iter, TFloat t,int& iter){
  TFloat t1 = newton(&posicion,&velocidad,d,tolerancia,max_iter,t,iter);
  TFloat menos_uno_tf=TFloat(-1,pr);
  d.v0=menos_uno_tf*d.fr*velocidad(d,t1);
  d.h=TFloat(0.0,pr); // la altura despues del impacto es cero
  return t1;
}


int main(int argc, char* argv[]){

  Datos datos;
  int iter1,iter2,iter3;
  TFloat tolerancia;
  int max_iter;

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


// primer impacto
  TFloat t1=biseccion_n(&posicion,datos,1);
  t1=newton(&posicion,&velocidad,datos,tolerancia,max_iter,t1, iter1);

  printf("log t1=%10.20f posicion(t1)=%10.20f iter=%d\n",t1.dbl(),posicion(datos,t1).dbl(),iter1);

  for (TFloat i=TFloat(0,pr); i.dbl()<t1.dbl(); i=i+t1/TFloat(1000,pr)){
    printf("emt1 %10.20f %10.20f\n", i.dbl(), energiaMecanica(datos,i).dbl());
  }
  printf("emt1 %10.20f %10.20f\n", t1.dbl(), energiaMecanica(datos,t1).dbl());

  // despues del primer impacto cambian v0 y h
  datos.h=TFloat(0.0,pr);
  TFloat menos_uno_tf=TFloat(-1,pr);
  datos.v0=menos_uno_tf*datos.fr*velocidad(datos,t1);

  // altura maxima
  TFloat t_h_max=biseccion_n(&velocidad,datos,1);
  t_h_max=newton(&velocidad,&aceleracion,datos,tolerancia,max_iter,t_h_max,iter2);

  printf("log t_h_max=%10.20f velocidad(t_h_max)=%10.20f iter=%d\n",t_h_max.dbl(),velocidad(datos,t_h_max).dbl(),iter2);

  TFloat h_max=posicion(datos,t_h_max);

  // segundo impacto
  TFloat t2=biseccion_n(&posicion,datos,1);
  t2=newton(&posicion,&velocidad,datos,tolerancia,max_iter,t2,iter3);

  printf("log t2=%10.20f posicion(t2)=%10.20f iter=%d\n",t2.dbl(),posicion(datos,t2).dbl(),iter3);

  for (TFloat i=TFloat(0,pr); i.dbl()<t2.dbl(); i=i+t2/TFloat(1000,pr)){
    printf("emt2 %10.20f %10.20f\n", (t1+i).dbl(), energiaMecanica(datos,i).dbl());
  }
  printf("emt2 %10.20f %10.20f\n", (t1+t2).dbl(), energiaMecanica(datos,t2).dbl());

  printf("%d %10.20f %d %10.20f %d %10.20f %d %10.20f %d\n",pr,tolerancia.dbl(),max_iter,t1.dbl(),iter1,h_max.dbl(),iter2,(t1+t2).dbl(),iter3);




  return 0;
}


