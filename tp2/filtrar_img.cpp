#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cassert>
#include "pgm.h"
#include "matriz.h"
#include "Banda.h"

using namespace std;

//
// MAIN
//
int main(int argc, char* argv[])
{
  if (argc<5) {
    cerr << "Error, ingrese parametros: imagen, lambda, factor_reduccion, archivo_salida\n";
    exit(1);
  }

  char *archivo=argv[1];
  double lambda=atof(argv[2]);
  int fr=atoi(argv[3]);
  char *archivo_salida=argv[4];

  assert(lambda>0);
  assert(fr >= 0 && fr <100);

  clock_t inicio, fin;
 
  inicio=clock();
  Pgm I;
  I.load(archivo,fr); // Carga

  int n=I.height();
  int m=I.width();
  Banda K(n*m,2*m+1);
  Matriz b(n*m,1);

  // Arma sistema
  for (int f = 2; f<=n-1; f++){
    for (int c = 2;c<=m-1;c++){
      K.sub((f-1)*m+c -1,(f-1)*m+c -1)   =  4+lambda;   // centro
      K.sub((f-1)*m+c -1,(f-2)*m+c -1)   = -1;          // arriba
      K.sub((f-1)*m+c -1,(f)*m+c -1)     = -1;          // abajo
      K.sub((f-1)*m+c -1,(f-1)*m+c-1 -1) = -1;          // izquierda
      K.sub((f-1)*m+c -1,(f-1)*m+c+1 -1) = -1;          // derecha
      b.sub((f-1)*m+c -1,0)             = lambda*I.sub(f -1,c -1);
    }
  }

  for (int c = 1;c<=m;c++){
    K.sub(c -1,c -1) = 1;                 // borde arriba
    b.sub(c -1,0) = I.sub(1 -1,c -1);
    
    K.sub((n-1)*m+c -1,(n-1)*m+c -1) = 1; // borde abajo
    b.sub((n-1)*m+c -1,0) = I.sub(n -1,c -1);
  }

  for (int f = 2;f<=n-1;f++){
    K.sub((f-1)*m+1 -1,(f-1)*m+1 -1) = 1; // borde izquierdo
    b.sub((f-1)*m+1 -1,0) = I.sub(f -1,1 -1);
    
    K.sub((f-1)*m+m -1,(f-1)*m+m -1) = 1; // borde derecho
    b.sub((f-1)*m+m -1,0) = I.sub(f -1,m -1);
  }


  Matriz x(n*m,1);
  K.resolverSistema(b,x);

  // Imagen filtrada
  int k=0;
  for (int i=0;i<I.height();i++){
    for (int j=0;j<I.width();j++){
      int gris=(int)x.sub(k++,0);
      if (gris > I.maxval()) gris = I.maxval();  // Por si el resultado se
      if (gris < 0) gris = 0;                    // va del rango [0,maxval]
      I.sub(i,j)=(int)gris;
    }
  }

  I.saveOrig(archivo_salida);       // Graba la imagen filtrada en tamaño original

  fin=clock();
  double segundos=(double)fin/CLOCKS_PER_SEC;

  cout << n << "x" << m << " " << fr << " " << lambda << " " << segundos << endl;

  return 0;
}
