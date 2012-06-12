#ifndef GIVENS
#define GIVENS

#include "Coef.h"
#include "matriz.h"

class Givens{
  public:
    Givens() {};
    Givens(int ii, int jj, Coef x1, Coef x2);



    // crea una nueva matriz donde guarda el producto; más adelante se puede mejorar pisando la matriz B
    Matriz operator*(const Matriz& B) const;




  private:
    int tam;
    int i;
    int j;
    Coef x_1;
    Coef x_2;

};





#endif
