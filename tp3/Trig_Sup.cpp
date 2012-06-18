#include <cassert>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


#include "matriz.h"
#include "Trig_Sup.h"

using namespace std;


Trig_Sup::Trig_Sup(int tamanio){
    assert(tamanio>0);
    tam=tamanio;
    cero=0;

    int elem=tam*(tam+1)/2;

    valores.resize(elem);

    //inicializo la matriz en cero
    for (int i=0;i<elem;i++){
        valores[i]=cero;
    }
}

Matriz Trig_Sup::operator*(const Matriz& B) const{
    assert(tam==B.cantFilas());
}
