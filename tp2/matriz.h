#include <vector>
#include <iostream>



typedef double Coef; //para zafar hacer un template

class Matriz{
public:
    Matriz(int m, int n);

    Matriz operator+(const Matriz& B) const;

    Matriz operator*(Coef k) const;

    void operator=(const Matriz& B);

    Matriz operator*(const Matriz& B) const;

    Matriz operator-(const Matriz& B) const;


    friend std::ostream& operator<<(std::ostream& os, const Matriz& A);

    Coef& sub(int i,int j);




private:
    int cantFils;
    int cantCols;

    std::vector<std::vector<Coef> > valores;


    void multiplicarFila(int i,Coef k);

    //me devuelve una copia de la fila
    Matriz fila(int i) const;

};

 Matriz operator*(Coef k,const Matriz& A);
