#include <iostream>
#include <vector>


typedef double Coef; //para zafar hacer un template

class Banda{

public:
        Banda(){};

        //matriz cuadrada de nxn, tam es n
        //una matriz pentadiagonal tiene nDiag=5
        Banda(int tam, int nDiag);

        Coef& sub(int i,int j);

private:
        int banda;
        int tam;
        Coef cero;

        std::vector<Coef> valores;
};
