#include <cassert>
#include <iostream>
#include <algorithm>

#include "matriz.h"


using namespace std;

Matriz::Matriz(int m, int n){
    cantFils=m;
    cantCols=n;

    //crea un vector de vectores
    valores=vector<vector<Coef> >(m, vector<Coef>(n,0));
}


Matriz Matriz::operator+(const Matriz& B) const{
    assert (cantFils==B.cantFils);
    assert (cantCols==B.cantCols);

    Matriz C(cantFils, cantCols);

    for (int i=0; i<cantFils; i++){
        for (int j=0; j<cantCols; j++){
            C.sub(i,j)=sub(i,j)+B.sub(i,j);
        }
    }
    return C;
}


ostream& operator<<(ostream& os, const Matriz& A){
    os << "[";
    for (int i=0; i < A.cantFils; i++){
        if (i>0){
            os << " ";
        }
        for (int j=0; j<A.cantCols;j++){
            os << A.sub(i,j) << ", ";
        }
        if (i==A.cantFils-1){
              os << "]";
        }
        os << endl;
    }
    return os;
}


Coef& Matriz::sub(int i,int j){
    assert (i>=0 && i<cantFils);
    assert (j>=0 && j<cantCols);
    return valores[i][j];
}


const Coef& Matriz::sub(int i,int j) const {
    assert (i>=0 && i<cantFils);
    assert (j>=0 && j<cantCols);
    return valores[i][j];
}


// las filas van de 0 a #filas-1
Matriz Matriz::fila(int i) const{
    assert (i>=0 && i<cantFils);
    Matriz f=Matriz(1,cantCols);
    for (int c=0; c<cantCols; c++){
        f.sub(0,c)=sub(i,c);
    }
    return f;
}


Matriz Matriz::operator*(Coef k) const{
    Matriz copia = *this;
    for (int i=0;i<cantFils;i++){
        copia.multiplicarFila(i,k);
    }
    return copia;
}


Matriz operator*(Coef k,const Matriz& A){
     return A*k;
}


void Matriz::multiplicarFila(int i,Coef k) {
   assert (i>=0 && i<cantFils);
   for (int c=0;c<cantCols;c++){
        valores[i][c]=sub(i,c)*k;
   }
}


Matriz Matriz::operator*(const Matriz& B) const{
    assert(cantCols==B.cantFils);
    Matriz C=Matriz(cantFils,B.cantCols);
    //defino a(i,j)
    for (int i=0; i<cantFils; i++){
        for(int j=0;j<B.cantCols;j++){
            for(int k=0;k<cantCols;k++)
                C.sub(i,j)=C.sub(i,j)+sub(i,k)*B.sub(k,j);
        }
    }
    return C;
}


Matriz Matriz::operator-(const Matriz& B) const{
    return *this+B*(-1);
}


int Matriz::cantFilas()const{
    return cantFils;
}


int Matriz::cantColms()const{
    return cantCols;
}


void Matriz::factorizacion_QR(Matriz& Q,Matriz& R)const{
  Q=Id(cantFilas());
  R=*this;

  for(int i=0; i<min(cantFilas(),cantColms())-1;i++){
    //limpio columna i
    for (int j=i+1;j<cantColms();j++){
        R.Givens_aux(i,j,Q);
    }
  }
}

void Matriz::Givens_aux(int i,int j,Matriz& Q){

}


Matriz Id(int n){
    Matriz I=Matriz(n,n);
    for (int i=0; i<n; i++){
        I.sub(i,i)=1;
    }
    return I;
}

