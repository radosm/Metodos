#ifndef TRIG_SUP
#define TRIG_SUP

#include <iostream>
#include <vector>

#include "matriz.h"
#include "Coef.h"

using namespace std;

class Trig_Sup{
    public:

        Trig_Sup(){};
        //matriz cuadrada de nxn, tam es n
        Trig_Sup(int tam);

        Matriz operator*(const Matriz& B) const;

    private:
        int tam;
        std::vector<Coef > valores;
        Coef cero;

};


#endif
