#include <cassert>
#include <iostream>
#include <algorithm>
#include <iostream>

#include "matriz.h"
#include "Matriz_Givens.h"


using namespace std;

Matriz::Matriz(int m, int n){
    cantFils=m;
    cantCols=n;

    //crea un vector de vectores
    valores=vector<vector<Coef> >(m, vector<Coef>(n,0));

    // para que no esté traspuesta
    traspuesta=false;
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
    os << "[ ";
    for (int i=0; i < A.cantFils; i++){
        if (i>0){
            os << "  ";
        }
        for (int j=0; j<A.cantCols;j++){
            os << A.sub(i,j) << ((j==(A.cantCols-1))?" ":", ");
        }
        if (i==A.cantFils-1){
              os << "]";
        }
        os << endl;
    }
    return os;
}


Coef& Matriz::sub(int i,int j){
    if (traspuesta) {
	swap(i, j);
    }
    assert (i>=0 && i<cantFils);
    assert (j>=0 && j<cantCols);
    return valores[i][j];
}


const Coef& Matriz::sub(int i,int j) const {
	if (traspuesta) {
		swap(i, j);
	}
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

  for(int i=0; i<min(cantFilas(),cantColms());i++){
    for (int j=i+1;j<cantColms();j++){
        Givens G=Givens(i,j,R.sub(i,i),R.sub(j,i),R.cantColms());
        G*R;
        G*Q;
    }
        //limpio columna i
//    for (int j=cantColms()-1;j>i;j--){
//       // Multiplico por la matriz G(i,j)
//        Givens G=Givens(j-1,j,R.sub(j,j-1),R.sub(j,j-1),R.cantColms());
//        cout << " G : " << endl << G << endl;
//        G*R;
//        cout << " R : " << endl << R << endl;
//       G*Q;
//    }
  }
  Q.trasponer();
}




Matriz Id(int n){
    Matriz I=Matriz(n,n);
    for (int i=0; i<n; i++){
        I.sub(i,i)=1;
    }
    return I;
}


void Matriz::trasponer(){
    traspuesta=not(traspuesta);
}

Coef modulo(Coef x){
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

Coef norma1(const Matriz& A){
    //norma uno es la "fila que más suma"
    Coef suma_max=0;

    for (int i=0; i<A.cantFilas();i++){
        Coef sum_aux=0;
        for (int j=0;j<A.cantColms();j++){
            //ojo que abs sólo funciona con double, long double y float!
            sum_aux+=modulo(A.sub(i,j));
        }
        if(sum_aux>suma_max){ suma_max=sum_aux;}
    }

    return suma_max;
}

void Matriz::autoval_autovect(Matriz& Qac, Matriz& Dant)const{
    int max_iter=2000;
    int max_tolerancia=0.001;
    int iter=1;
    Matriz A=*this;
    Qac=Id(A.cantFilas());

    int cantDiag=min(cantColms(),cantFilas());
    Dant=Matriz(cantDiag,1);
    //Dant=diag(A)
    for(int k=0;k<Dant.cantColms();k++){ Dant.sub(k,0)= A.sub(k,k); }

    //inicializo D como el vector nulo
    Matriz D=Matriz(cantDiag,1);

    Matriz Q;
    Matriz R;
    while(norma1(Dant-D)>max_tolerancia && iter<max_iter){
        A.factorizacion_QR(Q,R);
        A=R*Q;
        Qac=Qac*Q;
        Dant=D;
	//D=diag(A)
	for(int i=0;i<cantDiag;i++) D.sub(i,0)=A.sub(i,i);
        iter++;
    }
    // Los autovalores se almacenan en Dant y los autovectores en Qac
}

