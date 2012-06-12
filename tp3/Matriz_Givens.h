#ifndef GIVENS
#define GIVENS

#include "Coef.h"
#include "matriz.h"

class Givens{
  public:
    Givens() {};
    Givens(int ii, int jj, Coef x1, Coef x2);



    // Guarda el resultado de la multiplicaci�n en la matriz B
    void operator*(Matriz& B) const;




  private:
    int tam;
    int i;
    int j;
    Coef x_1;
    Coef x_2;

};



#endif