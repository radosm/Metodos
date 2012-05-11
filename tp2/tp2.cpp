#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"
#include "matriz.h"

using namespace std;

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
  Matriz K(n*m,n*m);
  Matriz b(n*m,1);

  J=I; // copia la imagen

  // Pone ruido en imagen J
  for (int i=0;i<J.height();i+=5){
    for (int j=0;j<J.width();j+=5){
      J.sub(i,j)=0;
    }
  }


  // Arma sistema
  for (int f=1;f<=n-2;f++){
    for (int c=1;c<=m-2;c++){
        K.sub( f*m+c, f *m+c)   =  4+lambda; // centro
        K.sub( f*m+c,(f-1)*m+c) = -1;        // arriba
        K.sub( f*m+c,(f+1)*m+c) = -1;        // abajo
        K.sub( f*m+c, f*m+c-1) = -1;        // izquierda
        K.sub( f*m+c, f*m+c+1) = -1;        // derecha
        b.sub( f*m+c,0)         = lambda*I.sub(f,c);
    }
  }

for (int c = 0; c<=m-1;c++){
    K.sub(c,c) = 1; // borde arriba
    b.sub(c,0) = I.sub(0,c);
   
    K.sub((n-1)*m+c,(n-1)*m+c) = 1; // borde abajo
    b.sub((n-1)*m+c,0) = I.sub(n-1,c);
}

for (int f = 1 ; f<=n-2;f++){
    K.sub(f*m+1,f*m+1) = 1; // borde izquierdo
    b.sub(f*m+1,0) = I.sub(f,0);

    K.sub(f*m+m,f*m+m) = 1; // borde derecho
    b.sub(f*m+m,0) = I.sub(f,m-1);
}

  I.save("blond_reducido.pgm");
  I.saveOrig("blond.pgm");
  J.save("blond_reducido_ruido.pgm");
  J.saveOrig("blond_ruido.pgm");

  return 0;
}
