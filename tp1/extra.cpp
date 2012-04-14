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
  TFloat tolerancia;
  TFloat acum;
  TFloat E;
  TFloat cota;
  int max_iter;
  int iter;
  int ci;

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
  acum=TFloat(0,pr);
  datos.h=TFloat(atof(argv[4]),pr);
  datos.v0=TFloat(atof(argv[5]),pr);
  datos.m=TFloat(atof(argv[6]),pr);
  datos.cr=TFloat(atof(argv[7]),pr);
  datos.fr=TFloat(atof(argv[8]),pr);

  cota=energiaMecanica(datos,TFloat(0,pr))*TFloat(0.0001,pr);
  E=TFloat(1,pr);
  
  ci=0;
  while (E.dbl()>cota.dbl() && ci < 200) {
    // Impacto
    TFloat t1=biseccion_n(&posicion,datos,5);
    t1=newton(&posicion,&velocidad,datos,tolerancia,max_iter,t1, iter);
    ci++;
    acum=acum+t1;

    E=energiaMecanica(datos,t1);

    //printf("log pr=%d t1=%10.20f posicion(t1)=%10.20f iter=%d cota=%10.20f E=%10.20f\n",pr,t1.dbl(),posicion(datos,t1).dbl(),iter,cota.dbl(),E.dbl());

    // despues del impacto cambian v0 y h
    datos.h=TFloat(0.0,pr);
    TFloat menos_uno_tf=TFloat(-1,pr);
    datos.v0=menos_uno_tf*datos.fr*velocidad(datos,t1);
  }

  if (ci==200) ci=-1; // infinito

  printf("pr=%d fr=%10.20f cr=%10.20f tiempo=%10.20f ci=%d\n",pr,datos.fr.dbl(),datos.cr.dbl(),acum.dbl(),ci);
  return 0;
}


