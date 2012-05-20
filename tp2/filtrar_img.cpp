#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cassert>
#include "pgm.h"
#include "matriz.h"
#include "Banda.h"

using namespace std;

Coef ECM(const Matriz& A, const Matriz& B){
    assert(A.cantFilas()==B.cantFilas());
    assert(A.cantColms()==B.cantColms());

    Coef acum=0;
    for (int i=0; i<A.cantFilas();i++){
        for(int j=0; j< A.cantColms();j++){
            //acum+=(A.sub(i,j)-B.sub(i,j))^2
            acum=acum+(A.sub(i,j)-B.sub(i,j))*(A.sub(i,j)-B.sub(i,j));
        }
    }

    //N es la cantidad de pixeles de la imagen
    int N=A.cantFilas()*A.cantColms();

    return acum/N;
}


Coef PSNR(const Matriz& A, const Matriz&B){
    Coef MAX=255;
    return 10*log10(MAX*MAX/ECM(A,B));
}


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
  Pgm I,I_sr;
  I.load(archivo,fr); // Carga
  I_sr.load(archivo); // Carga

  Matriz Orig(I_sr.height(),I_sr.width());

  for (int i=0; i<I_sr.height(); i++){
    for (int j=0; j<I_sr.width(); j++){
      Orig.sub(i,j)=I_sr.sub(i,j);
    }
  }

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

  Pgm I_filtrada_sr;
  I_filtrada_sr.resizeOrig(I);
  I_filtrada_sr.save(archivo_salida);
  I.saveOrig(archivo_salida);       // Graba la imagen filtrada en tamaño original

  Matriz Filt(I_filtrada_sr.height(),I_filtrada_sr.width());

  for (int i=0; i<I_sr.height(); i++){
    for (int j=0; j<I_filtrada_sr.width(); j++){
      Filt.sub(i,j)=I_filtrada_sr.sub(i,j);
    }
  }

  Coef psnr=PSNR(Orig,Filt);
  fin=clock();
  double segundos=(double)fin/CLOCKS_PER_SEC;

  cout << n << "x" << m << " " << fr << " " << lambda << " " << segundos << " " << psnr << endl;

  return 0;
}
