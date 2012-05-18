#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include "pgm.h"
#include "matriz.h"
#include "Banda.h"

using namespace std;

//
// Se pueden saber los valores de la matriz K sin necesidad de almacenarla
// Igual no se gana nada porque es necesario el espacio para la fact LU
//
double Ksub(int i,int j,int n,int m, double lambda){
  // borde
  if ((i>=0 && i<m-1) || (i%m)==0 || (i%m)==(m-1) || (i>=((n-1)*m) && i<(n*m-1))){
    if (i==j) return 1; else return 0;
  } 
  // fuera del borde
  if (i==j) return 4+lambda;
  if (j==(i-1) || j==(i+1) || j==(i+m) || j==(i-m)) return -1;
  return 0;
}


//
// MAIN
//
int main(int argc, char* argv[])
{
  if (argc<4) {
    cerr << "Error, ingrese parametros: imagen, lambda, factor_reduccion\n";
    exit(1);
  }

  char *archivo=argv[1];
  double lambda=atof(argv[2]);
  int fr=atoi(argv[3]);

  assert(lambda>0);
  assert(fr >= 0 && fr <100);

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

  I.save("salida_reducido.pgm");  // Graba la imagen filtrada reducida por fr
  I.saveOrig("salida.pgm");       // Graba la imagen filtrada en tamaño original

  return 0;
}
