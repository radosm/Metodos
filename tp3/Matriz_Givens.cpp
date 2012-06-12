#include <cassert>
#include <iostream>
#include <algorithm>

#include "Matriz_Givens.h"

using namespace std;

Givens::Givens(int ii, int jj, Coef x1, Coef x2){
    i=ii;
    j=jj;
    x_1=x1;
    x_2=x2;

}

