#include <iostream>

#include "matriz.h"


using namespace std;

int main()
{
    /*
    Matriz A=Matriz(2,3);
    Matriz B=Matriz(2,3);
    Matriz C=Matriz(1,3);
    cout << A << endl;
    //A.sub(1,1)=54;
    //cout << A<< endl;
    A.sub(1,2)=5156;
    A.sub(0,1)=-1;
    cout << A<< endl;
    cout << A.fila(0)<< endl;
    cout << A.fila(1)<< endl;
    */

    /*
    Matriz A=Matriz(2,3);
    A.sub(1,2)=5156;
    A.sub(0,1)=-1;
    cout << A<< endl;
    A=A*3;
    cout << A<< endl;
    A=2*A;
    cout << A<< endl;*/

    /*
    Matriz A=Matriz(3,3);
    A.sub(0,0)=2;
    A.sub(0,2)=1;
    A.sub(1,0)=3;
    A.sub(2,0)=5;
    A.sub(2,1)=1;
    A.sub(2,2)=1;
    cout << "A:" << endl << A<< endl;

    Matriz B=Matriz(3,3);
    B.sub(0,0)=1;
    B.sub(0,2)=1;
    B.sub(1,0)=1;
    B.sub(1,1)=2;
    B.sub(1,2)=1;
    B.sub(2,0)=1;
    B.sub(2,1)=1;
    cout << "B: " << endl << B<< endl;
    */
//
//    Matriz B=A;
//    cout << "B=A entonces B: " << endl << B<< endl;
//
//    Matriz A=A-B;
//    cout << "A-B: " << endl << A<< endl;
    /*Matriz C=A*B;
    cout << "A*B: " << endl << C<< endl;*/

    /*
    Matriz A=Matriz(3,3);
    A.sub(0,0)=1;
    A.sub(0,1)=-1;
    A.sub(0,2)=1;
    A.sub(1,0)=5;
    A.sub(1,1)=0;
    A.sub(1,2)=20;
    A.sub(2,0)=0;
    A.sub(2,1)=10;
    A.sub(2,2)=-20;
    cout << "A:" << endl << A<< endl;
    */

    /*
    Matriz L, U, P;
    A.descomposicionPLU(L,U,P);
    cout << "A:" << endl << A<< endl;

    A.intercambiarFilas(0,2);
    cout << "cambio filas 1 y 3, A:" << endl << A<< endl;

    A.descomposicionPLU(L,U,P);
    cout << "A:" << endl << A<< endl;
    */

    /*
    Matriz B=Matriz(3,3);
    B.sub(0,0)=1;
    B.sub(0,1)=1;
    B.sub(0,2)=1;
    B.sub(1,0)=1;
    B.sub(1,1)=2;
    B.sub(1,2)=1;
    B.sub(2,0)=1;
    B.sub(2,1)=1;
    B.sub(2,2)=1;
    */


//    Matriz A=Matriz(3,3);
//    A.sub(0,0)=1;
//    A.sub(0,1)=1;
//    A.sub(0,2)=1;
//    A.sub(1,0)=0;
//    A.sub(1,1)=1;
//    A.sub(1,2)=1;
//    A.sub(2,0)=0;
//    A.sub(2,1)=0;
//    A.sub(2,2)=1;
//    cout << "A:" << endl << A<< endl;
//
//    Matriz b=Matriz(3,1);
//    b.sub(0,0)=1;
//    b.sub(1,0)=1;
//    b.sub(2,0)=1;
//    cout << "b:" << endl << b << endl;
//
//    Matriz x;
//
//    A.resolverSistema(b,x);
//    cout << "x :" << endl << x << endl;
//

//    Matriz A=Matriz(3,3);
//    A.sub(0,0)=2;
//    A.sub(0,1)=2;
//    A.sub(0,2)=3;
//    A.sub(1,0)=4;
//    A.sub(1,1)=7;
//    A.sub(1,2)=7;
//    A.sub(2,0)=-2;
//    A.sub(2,1)=4;
//    A.sub(2,2)=5;
//    cout << "A: " << endl << A<< endl;
//
//    Matriz b=Matriz(3,1);
//    b.sub(0,0)=3;
//    b.sub(1,0)=1;
//    b.sub(2,0)=-7;
//    cout << "b: " << endl << b << endl;
//
//    Matriz x;
//
//    A.resolverSistema(b,x);
//    cout << "x :" << endl << x << endl;
//

    Matriz A=Matriz(5,5);
    A.sub(0,0)=2;
    A.sub(0,1)=2;
    A.sub(0,2)=3;
    A.sub(0,3)=3;
    A.sub(0,4)=3;
    A.sub(1,0)=4;
    A.sub(1,1)=7;
    A.sub(1,2)=7;
    A.sub(1,3)=7;
    A.sub(1,4)=7;
    A.sub(2,0)=-2;
    A.sub(2,1)=4;
    A.sub(2,2)=5;
    A.sub(2,3)=5;
    A.sub(2,4)=5;
    A.sub(3,0)=4;
    A.sub(3,1)=7;
    A.sub(3,2)=7;
    A.sub(3,3)=7;
    A.sub(3,4)=7;
    A.sub(4,0)=2;
    A.sub(4,1)=2;
    A.sub(4,2)=3;
    A.sub(4,3)=3;
    A.sub(4,4)=3;
    cout << "A: " << endl << A<< endl;

    Banda B=Banda(5,3);
    for (int i=0;i<5;i++){
        B.sub(i,i)=1;
//        if (i<4){
//            cout <<"trat�!"<< endl;
//            int j=i+1;
//            B.sub(i,j)=1;
//            cout << "sigo tratando" << endl;
//        }
    }

    B.sub(0,1)=13;
    cout << "trate" << endl;
    cout <<B.sub(0,1)<<endl;

    cout << "B :" << endl << B << endl;

    cout <<"A*B :" << endl << A*B << endl;

    return 0;
}














