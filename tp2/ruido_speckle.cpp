#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cassert>
#include "pgm.h"

using namespace std;

double rand_normal(void) {
  static double n2 = 0.0;
  static int n2_cached = 0;
  if (!n2_cached) { // la transformacion da dos valores se devuelve 1 
                    // y el otro se devuelve en la proxima llamada

    // Elegir un punto x,y en la bola unitaria, x,y con distrib uniforme
    double x, y, r;
    do {
      // Convertir x e y al [-1,1] y solo seguir si el radio entre 0 y (x,y) < 1
      x = 2.0*rand()/RAND_MAX - 1;
      y = 2.0*rand()/RAND_MAX - 1;
      r = x*x + y*y;
    } while (r == 0.0 || r > 1.0);
    // aplicar transformacion de Box-Muller a x e y
    double d = sqrt(-2.0*log(r)/r);
    double n1 = x*d;
    n2 = y*d;
    double result = n1;
    n2_cached = 1;
    return result;
    } else {
      n2_cached = 0;
      return n2;
    }
}

int main(int argc, char* argv[])
{
  if (argc<4) {
    cerr << "Error, ingrese parametros: archivo_entrada, archivo_salida, a\n";
    exit(1);
  }

  char *archivo=argv[1];
  char *archivosal=argv[2];
  double a=atof(argv[3]);

  assert (a>0);

  Pgm I;
  I.load(archivo); // Carga

  int n=I.height();
  int m=I.width();

  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      int gris=( (I.sub(i,j)/(double)I.maxval()) * (1+rand_normal()*sqrt(a)) )*I.maxval();
      if (gris > I.maxval()) gris = I.maxval();
      if (gris < 0) gris = 0;
      I.sub(i,j)=gris;
    }
  }

  I.save(archivosal);

  return 0;
}


