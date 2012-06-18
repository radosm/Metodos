#include <iostream>

using namespace std;

#include "matriz.h"
#include "Matriz_Givens.h"

int main()
{
    cout << "Hello world!" << endl;
    Matriz A=Id(3);
    cout << A << endl;
    A.sub(1,0)=2;
    cout << "A : " << endl << A << endl;
    //Givens G=Givens(1,0,A.sub(0,0),A.sub(1,0),A.cantColms());
    //cout << "G(2,1) : " << endl << G << endl;
    //G.trasponer();
    //cout << "G(2,1) : " << endl << G << endl;
    //cout << "A : " << endl << A << endl;
    //G*A;
    //cout << "G(2,1)*A : " << endl << A << endl;
    Matriz Q;
    Matriz R;
    A.factorizacion_QR(Q,R);
    cout << "Q*R : " << endl << Q*R << endl;
    cout << "Q : " << endl << Q << endl;
    cout << "R : " << endl << R << endl;
    cout << "A : "<< endl << A << endl;
    //A.trasponer();
    //cout << "A traspuesta: " << endl << A << endl;
    Matriz B=Id(15)*5;
    Matriz Qac;
    Matriz Dant;
    B.autoval_autovect(Qac,Dant);
    cout << " B : " << endl << B << endl;
    cout << " Qac : " << endl << Qac << endl;
    cout << " Dant : " << endl << Dant << endl;

    return 0;
}


