#include <iostream>
#include <stdio.h>
#include "pgm.h"


using namespace std;

int main()
{
  Pgm I,J;
  //I.load("64x64/blond.pgm"); // Carga
  I.load("/home/martin/Downloads/original.pgm",0); // Carga
  //I.load("256x256/goldhill.pgm",31); // Carga

cout << "w: " << I.width() << " h: " << I.height() << " m: " << I.maxval() << endl;
  J=I; // copia la imagen

/*
  // Pone ruido en imagen J
  for (int i=0;i<J.height();i+=10){
    for (int j=0;j<J.width();j+=10){
      J.sub(i,j)=0;
    }
  }
*/

  I.save("koko_reducido.pgm");
  I.saveOrig("koko.pgm");
  J.save("koko_reducido_ruido.pgm");
  J.saveOrig("koko_ruido.pgm");

  return 0;
}
