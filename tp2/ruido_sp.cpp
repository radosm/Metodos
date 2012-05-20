#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cassert>
#include "pgm.h"

using namespace std;

int main(int argc, char* argv[])
{
  if (argc<5) {
    cerr << "Error, ingrese parametros: archivo_entrada, archivo_salida, p, q\n";
    exit(1);
  }

  char *archivo=argv[1];
  char *archivosal=argv[2];
  double p=atof(argv[3]);
  double q=atof(argv[4]);
 
  assert(0<=p && p<=q && q<=1);

  Pgm I;
  I.load(archivo); // Carga

  int n=I.height();
  int m=I.width();

  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      double r=(double)rand()/(double)RAND_MAX;
      if (r < p) I.sub(i,j)=0;
      if (r > q) I.sub(i,j)=I.maxval();
    }
  }

  I.save(archivosal);

  return 0;
}


