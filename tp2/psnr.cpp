#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cassert>
#include "pgm.h"
#include "matriz.h"

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
  if (argc<3) {
    cerr << "Error, ingrese parametros: imagen1, imagen2\n";
    exit(1);
  }

  char *archivo1=argv[1];
  char *archivo2=argv[2];

  Pgm I,J;

  I.load(archivo1);
  J.load(archivo2);

  assert(I.height()==J.height() && I.width()==J.width());

  Matriz Img1(I.height(),I.width());
  Matriz Img2(J.height(),J.width());

  for (int i=0; i<I.height(); i++){
    for (int j=0; j<I.width(); j++){
      Img1.sub(i,j)=I.sub(i,j);
      Img2.sub(i,j)=J.sub(i,j);
    }
  }

  Coef psnr=PSNR(Img1,Img2);

  cout << psnr << endl;

  return 0;
}
