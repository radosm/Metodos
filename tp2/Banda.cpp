#include <cassert>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "Banda.h"


using namespace std;

Banda::Banda(int tam, int nDiag){
    assert(nDiag>=1 and nDiag<=(2*tam-1));
    tam=tam;
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

    //si estoy fuera de la banda
    if (abs(i-j)>(banda-1)/2){
        return cero;
    }

    int indice=0;
    // si estoy en la diagonal principal
    if (i==j){ indice=i;
    }else {
    //la diagonal en la que está el elemento
    int k=abs(i-j);
    indice=tam+2*(k-1)*tam+(k-1)*k;
        if (i>j){
            indice=indice+j;
        }else{
            indice=indice+tam+i;
        }
    }
    return valores[indice];
}

Coef& Banda::sub(int i,int j){

    //si estoy fuera de la banda
    if (abs(i-j)>(banda-1)/2){
        return cero;
    }

    int indice=0;
    // si estoy en la diagonal principal
    if (i==j){ indice=i;
    }else {
    //la diagonal en la que está el elemento
    int k=abs(i-j);
    indice=tam+2*(k-1)*tam+(k-1)*k;
        if (i>j){
            indice=indice+j;
        }else{
            indice=indice+tam+i;
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
        cout << "i'm trying!" << endl;
        if (i>0){
            os << " ";
        }
        cout << "stil here!" << endl;
        for (int j=0; j<B.columnas();j++){
            cout << "intento" << endl;
            os << B.sub(i,j) << ", ";
        }
        if (i==B.filas()-1){
              os << "]";
        }
        os << endl;
    }
    return os;
}
