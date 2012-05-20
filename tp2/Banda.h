#include <iostream>
#include <vector>

#include "matriz.h"


typedef double Coef; //para zafar hacer un template

class Banda{

public:
        Banda(){};
        //matriz cuadrada de nxn, tam es n
        //una matriz pentadiagonal tiene nDiag=5
        Banda(int tam, int nDiag);

        int cantDiag() const;

        int filas()const;
        int columnas()const;

        const Coef sub(int i,int j)const;
        Coef& sub(int i,int j);

        //pre: la matriz implicita tiene descomposicion LU sin pivoteo
        void descomposicionLU(Banda& L, Banda& U)const;

        void descomposicionLU();
        void resolverTrigInf_aux(const Matriz& y,Matriz& z);


        Matriz resolverSistema_const(const Matriz& b,Matriz& x) const;
        void resolverTrigSup(const Matriz& b,Matriz& y);
        void resolverTrigInf(const Matriz& y,Matriz& z);

        Matriz resolverSistema(const Matriz& b, Matriz& x);
        void resolverGauss(Matriz& b, Matriz& x);

        friend std::ostream& operator<<(std::ostream& os, const Banda& B);


private:
        int banda;
        int tam;
        Coef cero;

        std::vector<Coef> valores;
};
