#ifndef _MATRIZ_H_
#define _MATRIZ_H_

#include <vector>
#include <iostream>


typedef double Coef; //para zafar hacer un template



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


private:
    int cantFils;
    int cantCols;

    std::vector<std::vector<Coef> > valores;


    void multiplicarFila(int i,Coef k);

    //me devuelve una copia de la fila
    Matriz fila(int i) const;


};


Matriz operator*(Coef k,const Matriz& A);



#endif
