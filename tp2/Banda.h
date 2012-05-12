#include <iostream>
#include <vector>


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

        const Coef& sub(int i,int j)const;
        Coef& sub(int i,int j);

        friend std::ostream& operator<<(std::ostream& os, const Banda& B);


private:
        int banda;
        int tam;
        Coef cero;

        std::vector<Coef> valores;
};
