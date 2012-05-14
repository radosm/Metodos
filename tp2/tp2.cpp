#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"
#include "matriz.h"
#include "Banda.h"

using namespace std;

// Subindices de la matriz K
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

int main(int argc, char* argv[])
{
  if (argc<4) {
    cerr << "Error, ingrese parametros: imagen, lambda, factor_reduccion\n";
    exit(1);
  }

  char *archivo=argv[1];
  double lambda=atof(argv[2]);
  int fr=atoi(argv[3]);

  Pgm I,J;
  I.load(archivo,fr); // Carga

  int n=I.height();
  int m=I.width();
  Banda K(n*m,2*m+1);
  Matriz b(n*m,1);

  J=I; // copia la imagen

  // Pone ruido en imagen I
  for (int i=0;i<J.height();i+=5){
    for (int j=0;j<J.width();j+=5){
      I.sub(i,j)=0;
    }
  }


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

  // Graba matriz K
  ofstream f("K.matriz");
/*
  for (int i=0;i<n*m;i++){
    for (int j=0;j<n*m;j++){
      f << K.sub(i,j) << " ";
    }
    f << endl;
  }
*/
  f.close();
  // Graba matriz K producida por Ksub
  f.open("K.matriz.Ksub");
  for (int i=0;i<n*m;i++){
    for (int j=0;j<n*m;j++){
      f << Ksub(i,j,n,m,lambda) << " ";
    }
    f << endl;
  }
  f.close();

  // Graba vector b
  f.open("b.vector");
  for (int i=0;i<n*m;i++){
      f << b.sub(i,0) << endl;
  }
  f.close();

  // Imagen filtrada
  int k=0;
  for (int i=0;i<J.height();i++){
    for (int j=0;j<J.width();j++){
      int gris=(int)x.sub(k++,0);
      if (gris > J.maxval()) gris = J.maxval();
      if (gris < 0) gris = 0;
      J.sub(i,j)=(int)gris;
    }
  }

  // Graba dimensiones de la imagen
  f.open("dimensiones");
  f << n << " " << m << endl;
  f.close();

  J.save("salida_reducido.pgm");
  J.saveOrig("salida.pgm");
  I.saveOrig("original.pgm");

  return 0;
}
