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


int main(int argc, char* argv[]){

  Datos datos;
  int iter1,iter2,iter3;
  TFloat tolerancia;
  double incremento;
  int max_iter;

  if (argc<8) {
    cerr << "Error, ingrese parametros: precision, tolerancia, max_iter, altura inicial, velocidad inicial, masa, coeficiente de rozamiento, factor de restitucion\n"; 
    exit(1);
  }
  
  // Lectura de parametros y seteo de variables globales
  pr=(size_t)atoi(argv[1]);
  assert (pr>=1 && pr <=52);
  
  g = TFloat(9.81,pr);

  tolerancia=TFloat(atof(argv[2]),pr);
  max_iter=atoi(argv[3]);

  // Generacion de struct con los parametros
  datos.h=TFloat(atof(argv[4]),pr);
  datos.v0=TFloat(atof(argv[5]),pr);
  datos.m=TFloat(atof(argv[6]),pr);
  datos.cr=TFloat(atof(argv[7]),pr);
  datos.fr=TFloat(atof(argv[8]),pr);


  // Primer impacto
  TFloat t1=biseccion_n(&posicion,datos,5);
  t1=newton(&posicion,&velocidad,datos,tolerancia,max_iter,t1, iter1);
  printf("log pr=%d t1=%10.20f posicion(t1)=%10.20f iter=%d\n",pr,t1.dbl(),posicion(datos,t1).dbl(),iter1);

  // Energia mecanica hasta t1
  incremento=t1.dbl()/9.0;
  printf("emt1 %d %10.20f %10.20f\n",pr, 0.1, energiaMecanica(datos,TFloat(0.1)).dbl());
  for (int i=1; i<9 ; i++){
    printf("emt1 %d %10.20f %10.20f\n",pr, incremento*i, energiaMecanica(datos,TFloat(incremento*i,pr)).dbl());
  }
  printf("emt1 %d %10.20f %10.20f\n",pr, t1.dbl(), energiaMecanica(datos,t1).dbl());

  // despues del primer impacto cambian v0 y h
  datos.h=TFloat(0.0,pr);
  TFloat menos_uno_tf=TFloat(-1,pr);
  datos.v0=menos_uno_tf*datos.fr*velocidad(datos,t1);

  // Altura maxima
  TFloat t_h_max=biseccion_n(&velocidad,datos,5);
  t_h_max=newton(&velocidad,&aceleracion,datos,tolerancia,max_iter,t_h_max,iter2);

  printf("log pr=%d t_h_max=%10.20f velocidad(t_h_max)=%10.20f iter=%d posicion(t_h_max)=%10.20f\n",pr,t_h_max.dbl(),velocidad(datos,t_h_max).dbl(),iter2,posicion(datos,t_h_max).dbl());

  TFloat h_max=posicion(datos,t_h_max);

  // Segundo impacto
  TFloat t2=biseccion_n(&posicion,datos,5);
  t2=newton(&posicion,&velocidad,datos,tolerancia,max_iter,t2,iter3);

  printf("log pr=%d t2=%10.20f posicion(t2)=%10.20f iter=%d\n",pr,t2.dbl(),posicion(datos,t2).dbl(),iter3);

  // Energia mecanica entre t1 y t2
  incremento=t2.dbl()/10.0;
  for (int i=1; i<10 ; i++){
    printf("emt2 %d %10.20f %10.20f\n", pr,t1.dbl()+incremento*i, energiaMecanica(datos,TFloat(incremento*i,pr)).dbl());
  }
  printf("emt2 %d %10.20f %10.20f\n", pr,  (t1+t2).dbl(), energiaMecanica(datos,t2).dbl());

  // Resultado en una sola linea
  printf("%d %10.20f %d %10.20f %d %10.20f %d\n",pr,t1.dbl(),iter1,h_max.dbl(),iter2,(t1+t2).dbl(),iter3);

  return 0;
}


