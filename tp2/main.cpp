#include <iostream>

#include "Banda.h"


using namespace std;

int main()
{

//
//    Banda B=Banda(3,5);
//    B.sub(0,0)=2;
//    B.sub(0,1)=3;
//    B.sub(0,2)=4;
//    B.sub(1,0)=4;
//    B.sub(1,1)=5;
//    B.sub(1,2)=10;
//    B.sub(2,0)=4;
//    B.sub(2,1)=8;
//    B.sub(2,2)=2;
//    cout << "B : " << endl << B << endl;
////
////    Banda L,U;
////    B.descomposicionLU(L,U);
////
////    cout << "L : " << endl << L << endl;
////    cout << "U : " << endl << U << endl;
//
//    Matriz b= Matriz(3,1);
//    b.sub(0,0)=6;
//    b.sub(1,0)=16;
//    b.sub(2,0)=2;
//    cout << "b : " <<  endl <<b << endl;
//
//    Matriz x;
//    B.resolverSistema(b,x);
//
//    cout <<"x: " << endl << x << endl;

    Banda C=Banda(3,5);
    C.sub(0,0)=60;
    C.sub(0,1)=30;
    C.sub(0,2)=20;
    C.sub(1,0)=30;
    C.sub(1,1)=20;
    C.sub(1,2)=15;
    C.sub(2,0)=20;
    C.sub(2,1)=15;
    C.sub(2,2)=12;
    cout << "C : " << endl << C << endl;

    Matriz b_2= Matriz(3,1);
    b_2.sub(0,0)=180;
    b_2.sub(1,0)=115;
    b_2.sub(2,0)=86;
    cout << "b : " <<  endl <<b_2 << endl;

    Matriz x;
    C.resolverSistema(b_2,x);

    cout <<"x: " << endl << x << endl;


    return 0;
}






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
//
//    Matriz A=Matriz(5,5);
//    A.sub(0,0)=2;
//    A.sub(0,1)=2;
//    A.sub(0,2)=3;
//    A.sub(0,3)=3;
//    A.sub(0,4)=3;
//    A.sub(1,0)=4;
//    A.sub(1,1)=7;
//    A.sub(1,2)=7;
//    A.sub(1,3)=7;
//    A.sub(1,4)=7;
//    A.sub(2,0)=-2;
//    A.sub(2,1)=4;
//    A.sub(2,2)=5;
//    A.sub(2,3)=5;
//    A.sub(2,4)=5;
//    A.sub(3,0)=4;
//    A.sub(3,1)=7;
//    A.sub(3,2)=7;
//    A.sub(3,3)=7;
//    A.sub(3,4)=7;
//    A.sub(4,0)=2;
//    A.sub(4,1)=2;
//    A.sub(4,2)=3;
//    A.sub(4,3)=3;
//    A.sub(4,4)=3;
//    cout << "A: " << endl << A<< endl;


//
//    Banda B=Banda(5,3);
//    for (int i=0;i<5;i++){
//        B.sub(i,i)=1;
//        if (i<4){
//            int j=i+1;
//            B.sub(i,j)=1;
//        }
//    }
//
//
//
//    B.sub(0,1)=13;
//
//    cout << "B :" << endl << B << endl;
//
//    cout <<"A*B :" << endl << A*B << endl;
//
//    return 0;




