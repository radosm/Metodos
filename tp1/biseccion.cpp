#include "iostream"
#include "math.h"
#include "TFloat.h"
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "fisica.h"
#include "metodos.h"

using namespace std;

size_t pr;

TFloat g;


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
  TFloat t1;
  t1=biseccion(&posicion,datos,tolerancia,max_iter,iter1);
  //printf("posicion(t1)=%10.20f\n",posicion(datos,t1).dbl());

  for (TFloat i=TFloat(0,pr); i.dbl()<t1.dbl(); i=i+t1/TFloat(1000,pr)){
    printf("emt1 %10.20f %10.20f\n", i.dbl(), energiaMecanica(datos,i).dbl());
  }
  printf("emt1 %10.20f %10.20f\n", t1.dbl(), energiaMecanica(datos,t1).dbl());

  // despues del primer impacto cambian v0 y h
  datos.h=TFloat(0.0,pr);
  TFloat menos_uno_tf=TFloat(-1,pr);
  datos.v0=menos_uno_tf*datos.fr*velocidad(datos,t1);

  // altura maxima
  TFloat t_h_max=biseccion(&velocidad,datos,tolerancia,max_iter,iter2);
  TFloat h_max=posicion(datos,t_h_max);

  // segundo impacto
  TFloat t2;
  t2=biseccion(&posicion,datos,tolerancia,max_iter,iter3);
  for (TFloat i=TFloat(0,pr); i.dbl()<t2.dbl(); i=i+t2/TFloat(1000,pr)){
    printf("emt2 %10.20f %10.20f\n", (t1+i).dbl(), energiaMecanica(datos,i).dbl());
  }
  printf("emt2 %10.20f %10.20f\n", (t1+t2).dbl(), energiaMecanica(datos,t2).dbl());

  printf("%d %10.20f %d %10.20f %d %10.20f %d %10.20f %d\n",pr,tolerancia.dbl(),max_iter,t1.dbl(),iter1,h_max.dbl(),iter2,(t1+t2).dbl(),iter3);

  return 0;
}
