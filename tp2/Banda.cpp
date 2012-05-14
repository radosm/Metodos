#include <cassert>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "Banda.h"
#include "matriz.h"


using namespace std;

Banda::Banda(int tamanio, int nDiag){
    assert(nDiag>=1 and nDiag<=(2*tamanio-1));
    tam=tamanio;
    banda=nDiag;
    cero=0;

    //calculo cuántos elementos tengo que guardar
    //aux: guardo n de la diagonal, 2(n-1) las diagonales inmediatas, 2(n-2) las siguientes y así
    //int cantElem=tam;
    //for (int k=(nDiag-1)/2;k>0;k=k-1){
        //cantElem=cantElem+2*(tam-k);
    //}

    int k=(nDiag-1)/2;
    int elem=tam+2*k*tam-k*(k+1);

    valores.resize(elem);

    //inicializo la matriz en cero
    for (int i=0;i<elem;i++){
        valores[i]=0;
    }

    //guardo los valores desde la diagonal hacia afuera

}

const Coef& Banda::sub(int i,int j)const{
    // si estoy fuera de la banda
    if (abs(i-j)>(banda-1)/2){
        return cero;
    }
    int indice=0;
    // si estoy en la diagonal principal
    if (i==j){
        indice=i;
    }else {
        //la diagonal en la que está el elemento
        int k=abs(i-j);
        indice=tam+2*(k-1)*tam-(k-1)*k;
        if (i>j){
            indice=indice+j;
        }else{
            indice=indice+tam-k+i;
        }
    }
    return valores[indice];
}


Coef& Banda::sub(int i,int j){
    //pre: estoy dentro de la banda (no quiero poder modificar los elementos fuera de la banda)
    // cout << "i=" << i << " j=" <<j  << endl;
    assert(abs(i-j)<=(banda-1)/2);

    int indice=0;
    // si estoy en la diagonal principal
    if (i==j){
        indice=i;
    }else {
        //la diagonal en la que está el elemento
        int k=abs(i-j);
        indice=tam+2*(k-1)*tam-(k-1)*k;
        if (i>j){
            indice=indice+j;
        }else{
            indice=indice+tam-k+i;
        }
    }
    return valores[indice];
}

int Banda::cantDiag()const{
    return banda;
}


int Banda::filas()const{
    return tam;
}

int Banda::columnas()const{
    return tam;
}

ostream& operator<<(ostream& os, const Banda& B){
    os << "[";
    for (int i=0; i < B.filas(); i++){
        if (i>0){
            os << " ";
        }
        for (int j=0; j<B.columnas();j++){
            os << B.sub(i,j) << ", ";
        }
        if (i==B.filas()-1){
              os << "]";
        }
        os << endl;
    }
    return os;
}

Banda Id(int n,int banda){
    Banda Identidad=Banda(n,banda);
    for (int i=0; i<n;i++){
        Identidad.sub(i,i)=1;
    }
    return Identidad;
}


void Banda::descomposicionLU(Banda& L, Banda& U)const{
    U=*this;
    L=Id(filas(),banda);

    // i es el i-esimo paso de la triangulación
    for (int i=0;i<filas();i++){
        int k=(banda-1)/2;
        for(int j=i+1;j<min(filas(),k+1);j++){
        //fila j (j>i) ---> fila j-a(j,i)/a(i,i)*fila(i)
            Coef mult = U.sub(j,i) / U.sub(i,i);
            L.sub(j,i)=mult;
            for(int c=i;c<min(columnas(),k+1);c++){

                U.sub(j,c) = U.sub(j,c) - mult * U.sub(i,c);
            }
        }
    }
}


Matriz Banda::resolverSistema(const Matriz& b, Matriz& x) const{
    //tomo como pre que b sea vector columna
    assert(b.cantColms()==1);
    Banda L;
    Banda U;

    descomposicionLU(L,U);
    //Tengo que resolver Ax=b --> (tengo PA=LU) es equivalente a resolver PAx=Pb  ---> LUx=Pb  ---> (P es de permutacion, su inversa es su traspuesta)  traspuesta(P)LU=b


    //resuelvo Ly=b  ----> obtengo y
    Matriz y;
    L.resolverTrigInf(b,y);

    //resuelvo Ux=y
    U.resolverTrigSup(y,x);

    return x;

}


void Banda::resolverTrigSup(const Matriz& b,Matriz& y){
    //la matriz implícita es triangular superior
    //la matriz implícita es cuadrada
    assert(columnas()==filas());
    y=Matriz(b.cantFilas(),b.cantColms());
    y=b;
    //la diagonal no tiene ceros
    for(int i=0;i<columnas();i++){
        assert(sub(i,i)!=0);
    }

    for (int i=filas()-1;i>-1; i--){
        int k=(banda-1)/2;
        for(int j=i+1;j<min(columnas(),i+k+1);j++){
            y.sub(i,0)=y.sub(i,0)-sub(i,j);
        }

        y.sub(i,0)=y.sub(i,0)/sub(i,i);
        //multiplicar columna
        for(int f=i-1;f>max(-1,i-(k+1));f--){
            sub(f,i)=sub(f,i)*y.sub(i,0);
        }
    }
}


void Banda::resolverTrigInf(const Matriz& y,Matriz& z){
    //la matriz implícita es triangular inferior
    //la matriz implícita es cuadrada
    assert(columnas()==filas());
    z=Matriz(y.cantFilas(),y.cantColms());
    z=y;
    //la diagonal no tiene ceros
    for(int i=0;i<columnas();i++){
        assert(sub(i,i)!=0);
    }


    for (int i=0;i<filas(); i++){
        int k=(banda-1)/2;
        for(int j=i-1;j>max(-1,i-(k+1));j--){
            z.sub(i,0)=z.sub(i,0)-sub(i,j);
        }

        z.sub(i,0)=z.sub(i,0)/sub(i,i);

        //multiplicar columna
        for(int f=i+1;f<min(filas(),i+k+1);f++){
            sub(f,i)=sub(f,i)*z.sub(i,0);
        }
    }

}
