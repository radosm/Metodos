#include <cassert>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <math.h>

#include "Matriz_Givens.h"
#include "Coef.h"

using namespace std;

Coef norma2(Coef x1, Coef x2){
    return sqrt(x1*x1+x2*x2);
}

Givens::Givens(int ii, int jj, Coef x1, Coef x2){
    i=ii;
    j=jj;
    Coef norma=norma2(x1,x2);
    x_1=x1/norma;
    x_2=x2/norma;

}

void Givens::operator*(Matriz& B)const{
  Matriz fila_i=Matriz(1,B.cantColms());
  for (int k=0; k<B.cantColms();k++){
    cout << "ok "  << i << "   " << k << endl;
    fila_i.sub(1,k)=B.sub(i,k);
  }
  Matriz fila_j=Matriz(1,B.cantColms());
    for (int k=0; k<B.cantColms();k++){
    fila_j.sub(1,k)=B.sub(j,k);
  }

  //Multiplico
  for (int p=0; p<B.cantColms();p++){
    B.sub(i,p)=x_1*fila_i.sub(1,p)+x_2*fila_j.sub(1,p);
    B.sub(j,p)=x_1*fila_i.sub(1,p)-x_2*fila_j.sub(1,p);
  }
}


