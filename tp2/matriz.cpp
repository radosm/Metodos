#include <cassert>
#include <iostream>

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

//Matriz Matriz::operator*(const Matriz& B) const{
//    assert(cantCols==B.cantFils);
//    Matriz C=Matriz(cantFils,B.cantCols);
//    for (int i=0; i<cantFils; i++){
//        cout << "anda" << endl;
//        for(int j=0;j<cantCols;j++){
//            if (sub(i,j)!=0){
//                C.fila(i)=C.fila(i)+sub(i,j)*B.fila(j);
//            }
//        }
//    }
//        //el problema ac� es que C.fila(i) me da una copia de la fila, no la fila
                //C.fila(i)=C.fila(i)+sub(i,j)*B.fila(j);
//}

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

//pivotear devuelve true si hay alg�n pivote no nulo en la columna i, de fila i en adelante
bool Matriz::pivotear(Matriz& P,int i){
    //encontrar pivote
    int indice=-1;
    for(int j=i;j<cantFils;j++){
        if (sub(j,i)!=0){
            indice=j;
            break;
        }
    }
    //si toda la columna es cero, pasa a la siguiente columna
    if (indice==-1){ return false;}
    //intercambiar fila i de U con fila indice de U
    intercambiarFilas(i,indice);
    P.intercambiarFilas(i,indice);
    return true;
}

void Matriz::descomposicionPLU(Matriz& L, Matriz& U, Matriz& P)const{
    P=Id(cantFils);
    U=*this;
    L=Id(cantFils);

    // i es el i-esimo paso de la triangulaci�n
    for (int i=0;i<cantFils;i++){
        if (!U.pivotear(P,i)){ continue;}
        for(int j=i+1;j<cantFils;j++){
        //fila j (j>i) ---> fila j -a(j,i)/a(i,i)*fila(i)
            Coef mult = U.sub(j,i) / U.sub(i,i);
            L.sub(j,i)=mult;
            for(int c=i;c<cantCols;c++){
                U.sub(j,c) = U.sub(j,c) - mult * U.sub(i,c);
            }
        }
    }
    //cout << "L*U " << endl << L*U << endl;
    //cout << "P*A   " << endl << P*(*this) << endl;
}

Matriz Matriz::trasponer()const{
    Matriz T(cantCols,cantFils);
    for(int i=0;i<cantFils;i++){
        for (int j=0;cantCols;j++){
            T.sub(j,i)=sub(i,j);
        }
    }
    return T;
}

Matriz Id(int n){
    Matriz Identidad=Matriz(n,n);
    for (int i=0; i<n;i++){
        Identidad.sub(i,i)=1;
    }
    return Identidad;
}




void Matriz::intercambiarFilas(int i, int j){
    assert(i>=0 && i<cantFils);
    assert(j>=0 && j<cantFils);
    if (i==j) return;
    for (int k=0;k<cantCols;k++){
        swap(sub(i,k),sub(j,k));
    }
}

Matriz Matriz::resolverSistema(const Matriz& b, Matriz& x) const{
    //tomo como pre que b sea vector columna
    assert(b.cantCols==1);
    Matriz L;
    Matriz P;
    Matriz U;

    descomposicionPLU(L,U,P);

    //Tengo que resolver Ax=b --> (tengo PA=LU) es equivalente a resolver PAx=Pb  ---> LUx=Pb  ---> (P es de permutacion, su inversa es su traspuesta)  traspuesta(P)LU=b

    //resuelvo Ux=b  ----> obtengo y
    cout << "U: " << endl << U << endl;
    Matriz y;
    U.resolverTrigSup(b,y);
    cout << "despues de triangular," << endl << "U: " << endl << U << endl;
    cout << "solucion :" << endl << y << endl;

    //resuelvo Ly=b
    cout << "prueba 1" << endl;
    Matriz z;
    cout << "prueba 2" << endl;
    L.resolverTrigInf(y,z);
    cout << "prueba 3" << endl;

    //x=P.trasponer()*z;


}

void Matriz::resolverTrigSup(const Matriz& b,Matriz& y){
    //la matriz impl�cita es triangular superior
    //la matriz impl�cita es cuadrada
    assert(cantCols==cantFils);
    y=Matriz(b.cantFils,b.cantCols);
    y=b;
    //la diagonal no tiene ceros
    for(int i=0;i<cantCols;i++){
        assert(sub(i,i)!=0);
    }


    for (int i=cantFils-1;i>-1; i--){
        cout << "fila :" << i+1 << endl;
        for(int j=i+1;j<cantCols;j++){
            cout << "resto columna :" << j+1 << endl;
            y.sub(i,0)=y.sub(i,0)-sub(i,j);
        }

        cout << "b(" << i+1 << ") :" << y.sub(i,0)  << " (antes de dividir)"<< endl;
        y.sub(i,0)=y.sub(i,0)/sub(i,i);
        cout << "b(" << i+1 << ") :" << y.sub(i,0) << endl;
        //multiplicar columna
        for(int f=i-1;f>-1;f--){
            sub(f,i)=sub(f,i)*y.sub(i,0);
        }
    }
}


void Matriz::resolverTrigInf(const Matriz& y,Matriz& z){
    //la matriz impl�cita es triangular inferior
    //la matriz impl�cita es cuadrada
    assert(cantCols==cantFils);
    z=Matriz(y.cantFils,y.cantCols);
    z=y;
    //la diagonal no tiene ceros
    for(int i=0;i<cantCols;i++){
        assert(sub(i,i)!=0);
    }


    for (int i=0;i<cantFils; i++){

        for(int j=i-1;j>-1;j--){
            cout << "resto columna :" << j+1 << endl;
            z.sub(i,0)=z.sub(i,0)-sub(i,j);
        }

        z.sub(i,0)=z.sub(i,0)/sub(i,i);

        //multiplicar columna
        for(int f=i+1;f<cantFils;f++){
            sub(f,i)=sub(f,i)*z.sub(i,0);
        }
    }
    cout << "pude trig inf" << endl;
}
