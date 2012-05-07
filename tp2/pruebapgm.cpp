#include <iostream>
#include <stdio.h>
#include "pgm.h"


using namespace std;

int main()
{
  Pgm I,J;
  //I.load("64x64/blond.pgm"); // Carga
  //I.load("128x128/einstein.pgm"); // Carga
  I.load("256x256/goldhill.pgm"); // Carga

  J=I; // copia la imagen

  // Pone ruido en imagen J
  for (int i=0;i<J.height();i+=10){
    for (int j=0;j<J.width();j+=10){
      J.sub(i,j)=0;
    }
  }

  I.save("koko.pgm");
  J.save("koko_ruido.pgm");

  return 0;
}
