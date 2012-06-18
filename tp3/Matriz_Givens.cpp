#include <cassert>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <math.h>

#include "Matriz_Givens.h"
#include "Coef.h"
#include "matriz.h"

using namespace std;

Coef norma2(Coef x1, Coef x2){
    return sqrt(x1*x1+x2*x2);
}

Givens::Givens(int ii, int jj, Coef x1, Coef x2, int tamnio){
    i=ii;
    j=jj;
    Coef norma=norma2(x1,x2);
    x_1=x1/norma;
    x_2=x2/norma;
    tam=tamnio;

}

int Givens::tamanio() const{
    return tam;
}

void Givens::operator*(Matriz& B)const{
  Matriz fila_i=Matriz(1,B.cantColms());
  for (int k=0; k<B.cantColms();k++){
    fila_i.sub(0,k)=B.sub(i,k);
  }
  Matriz fila_j=Matriz(1,B.cantColms());
    for (int k=0; k<B.cantColms();k++){
    fila_j.sub(0,k)=B.sub(j,k);
  }

  for (int p=0; p<B.cantColms();p++){
    B.sub(i,p)=x_1*fila_i.sub(0,p)+x_2*fila_j.sub(0,p);
    B.sub(j,p)=-x_2*fila_i.sub(0,p)+x_1*fila_j.sub(0,p);
  }
}


std::ostream& operator<<(std::ostream& os, const Givens& G){
    Matriz IDD=Id(G.tamanio());
    G*IDD;
    os<<IDD;
    return os;
}



void Givens::trasponer(){
    x_2=-x_2;
}

void operator*(Matriz& A,const Givens& G){
    //el producto G*A, lo almaceno en A
    // Hago G_traspuesta * A traspuesta, y después traspongo
    Givens aux=G;
    aux.trasponer();
    A.trasponer();
    aux*A;
    A.trasponer();
}
