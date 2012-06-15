#ifndef _MATRIZ_H_
#define _MATRIZ_H_

#include <vector>
#include <iostream>

#include "Coef.h"


class Matriz{
public:
    Matriz() {};

    Matriz(int m, int n);

    Matriz operator+(const Matriz& B) const;

    Matriz operator*(Coef k) const;

    Matriz operator*(const Matriz& B) const;

    Matriz operator-(const Matriz& B) const;


    int cantFilas()const;
    int cantColms()const;



    friend std::ostream& operator<<(std::ostream& os, const Matriz& A);

    Coef& sub(int i,int j);
    const Coef& sub(int i,int j) const;

    void factorizacion_QR(Matriz& Q,Matriz& R)const;


private:
    int cantFils;
    int cantCols;

    std::vector<std::vector<Coef> > valores;


    void multiplicarFila(int i,Coef k);

    //me devuelve una copia de la fila
    Matriz fila(int i) const;

    void Givens_aux(int i,int j,Matriz& Q);


};


Matriz operator*(Coef k,const Matriz& A);
Matriz Id(int n);



#endif
